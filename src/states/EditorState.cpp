#include "EditorState.hpp"

EditorState::EditorState(StateData *stateData)
    : State(stateData)
{
    this->initDeferredRender();
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initText();
    this->initKeybinds();
    this->initPauseMenu();
    this->initButtons();
    this->initTileMap();
    this->initGui();
}

EditorState::~EditorState()
{
    for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }

    delete this->pmenu;
    delete this->map;
    delete this->textureSelector;
}

//Initialization
void EditorState::initVariables()
{
    //this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->statedata->gridSize), static_cast<int>(this->statedata->gridSize));
    this->cameraSpeed = 400.f;
}

void EditorState::initBackground()
{
}

void EditorState::initFonts()
{
    if (!this->font.loadFromFile("src/fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::EDITORSTATE::Could not load font");
    }
}

void EditorState::initKeybinds()
{
    std::ifstream ifs("src/config/editorstate_keybinds");
    if (ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2)
        {
            this->keybinds[key] = this->statedata->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void EditorState::initButtons()
{
}

void EditorState::initText()
{
    this->cursorText.setFont(this->font);
    this->cursorText.setFillColor(sf::Color::White);
    this->cursorText.setCharacterSize(12);
    this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y);
}

void EditorState::initPauseMenu()
{
    this->pmenu = new PauseMenu(*this->statedata->gfxSettings->window, &this->font);

    this->pmenu->addButton("QUIT", 500.f, "Quit");
    this->pmenu->addButton("SAVE", 300.f, "Save");
    this->pmenu->addButton("LOAD", 400.f, "Load");
}

void EditorState::initTileMap()
{
    this->map = new TileMap(this->statedata->gridSize, 5, 16, "src/images/Tiles/Stonex20.png");
}

void EditorState::initDeferredRender()
{
    this->renderTexture.create(
        this->statedata->gfxSettings->resolution.width,
        this->statedata->gfxSettings->resolution.height
    );
    this->renderSprite.setTexture(this->renderTexture.getTexture());
    this->renderSprite.setTextureRect(
        sf::IntRect(
            0, 0,
            this->statedata->gfxSettings->resolution.width,
            this->statedata->gfxSettings->resolution.height
        )
    );
}

sf::Vector2f EditorState::getViewOffset()
{
    return this->view.getCenter() - this->view.getSize() / 2.f;
}

void EditorState::initGui()
{
    this->sidebar.setSize(sf::Vector2f(60.f, static_cast<float>(this->statedata->gfxSettings->resolution.height)));
    this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
    this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
    this->sidebar.setOutlineThickness(1.f);

    this->selectorRect.setSize(sf::Vector2f(this->statedata->gridSize, this->statedata->gridSize));
    this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::Green);

    this->selectorRect.setTexture(TileRegistry::Instance()->getTexture(this->type));
    this->selectorRect.setTextureRect(sf::IntRect(0,0, static_cast<int>(this->statedata->gridSize), static_cast<int>(this->statedata->gridSize)));

    this->textureSelector = new gui::TextureSelector(10.f, 10.f, 400.f, 500.f, this->statedata->gridSize, 4, this->font, "Tex");
}

//Update
void EditorState::updateInput(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("PAUSE"))))
    {
        if (KeyState::getInstance()->PAUSE == false)
        {
            this->paused = !this->paused;
        }
        KeyState::getInstance()->PAUSE = true;
    }
    else
    {
        KeyState::getInstance()->PAUSE = false;
    }
}

void EditorState::updateButtons()
{
    for (auto &it : this->buttons)
    {
        it.second->update(this->mousePosWindow);
    }
}

void EditorState::update(const float &dt)
{
    this->updateMousePosition();
    this->updateKeyTime(dt);
    this->updateInput(dt);
    if (!this->paused)
    {
        this->updateButtons();
        this->updateGui(dt);
        this->updateEditorInput(dt);
    }
    else
    {
        this->pmenu->update(this->mousePosWindow);
        this->updatePauseMenu();
    }
}

void EditorState::updatePauseMenu()
{
    if (this->pmenu->isButtonPressed("QUIT"))
    {
        this->endState();
    }

    if (this->pmenu->isButtonPressed("SAVE"))
    {
        this->map->saveToFile("src/map.json");
    }

    if (this->pmenu->isButtonPressed("LOAD"))
    {
        this->map->loadFromFile("src/map.json");
    }
}

void EditorState::updateEditorInput(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CAMERA_UP"))))
    {
        this->view.move(0, -cameraSpeed * dt);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CAMERA_DOWN"))))
    {
        this->view.move(0, cameraSpeed * dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CAMERA_LEFT"))))
    {
        this->view.move(-cameraSpeed * dt, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CAMERA_RIGHT"))))
    {
        this->view.move(cameraSpeed * dt, 0);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime())
    {
        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
        {
            if (!this->textureSelector->getActive())
            {
                this->map->addTile(this->mousePosGridScaled.x, this->mousePosGridScaled.y, this->type);
            }
            else
            {
                this->type = this->textureSelector->getType();
                if (TileRegistry::Instance()->isCollision(type)) {
                    this->selectorRect.setOutlineColor(sf::Color::Red);
                }
                else {
                    this->selectorRect.setOutlineColor(sf::Color::Green);
                }
                this->selectorRect.setTexture(TileRegistry::Instance()->getTexture(type));
            }
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime())
    {
        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
        {
            if (!this->textureSelector->getActive())
            {
                this->map->removeTile(
                    this->mousePosGridScaled.x,
                    this->mousePosGridScaled.y,
                    0);
            }
        }
    }
}

void EditorState::updateGui(const float &dt)
{

    this->textureSelector->update(this->mousePosWindow, dt);
    if (!this->textureSelector->getActive())
    {
        this->selectorRect.setPosition(this->mousePosGridScaled.x * gridSize, this->mousePosGridScaled.y * gridSize);
    }

    this->cursorText.setPosition(
        this->mousePosView.x + 100.f + this->getViewOffset().x,
        this->mousePosView.y - 50.f + this->getViewOffset().y
    );
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y
       << "\n"
       << this->mousePosGridScaled.x << " " << this->mousePosGridScaled.y
       << "\n"
       << static_cast<int>(this->type);
    this->cursorText.setString(ss.str());
}

//Render
void EditorState::renderButtons(sf::RenderTarget *target)
{
    for (auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void EditorState::renderGui()
{
    if (!this->textureSelector->getActive())
    {
        this->renderTexture.setView(this->view);
        this->renderTexture.draw(this->selectorRect);
    }

    this->renderTexture.setView(this->statedata->gfxSettings->window->getDefaultView());
    this->textureSelector->render(this->renderTexture);
    this->renderTexture.draw(this->sidebar);
    this->renderTexture.setView(this->view);
    this->renderTexture.draw(this->cursorText);
}

void EditorState::render(sf::RenderTarget *target)
{
    if (!target)
        target = this->statedata->gfxSettings->window;

    this->renderTexture.clear();
    this->renderTexture.setView(this->view);
    this->map->render(this->renderTexture, true, this->mousePosGridScaled, sf::Vector2i(this->view.getCenter() / this->gridSize));
    this->map->renderDeferred(this->renderTexture, true);
    this->renderTexture.setView(this->statedata->gfxSettings->window->getDefaultView());
    this->renderButtons(&this->renderTexture);
    this->renderGui();

    if (this->paused)
    {
        this->renderTexture.setView(this->statedata->gfxSettings->window->getDefaultView());
        this->pmenu->render(this->renderTexture);
    }
    this->renderTexture.display();
    target->draw(this->renderSprite);
}