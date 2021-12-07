#include "EditorState.hpp"

EditorState::EditorState(StateData *stateData)
    : State(stateData)
{
    this->initVariables();
    this->initView();
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
    this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->statedata->gridSize), static_cast<int>(this->statedata->gridSize));
    this->collision = false;
    this->tileType = TileTypes::DEFAULT;
    this->cameraSpeed = 100.f;
}

void EditorState::initView()
{
    this->view.setSize(sf::Vector2f(
        this->statedata->gfxSettings->resolution.width,
        this->statedata->gfxSettings->resolution.height));

    this->view.setCenter(sf::Vector2f(
        this->statedata->gfxSettings->resolution.width / 2.f,
        this->statedata->gfxSettings->resolution.height / 2.f));
}

void EditorState::initBackground()
{
}

void EditorState::initFonts()
{
    if (!this->font.loadFromFile("fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::EDITORSTATE::Could not load font");
    }
}

void EditorState::initKeybinds()
{
    std::ifstream ifs("config/editorstate_keybinds");
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
    this->map = new TileMap(this->statedata->gridSize, 256, 256, "images/Tiles/tilesheet1.png");
}

void EditorState::initGui()
{
    this->sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(this->statedata->gfxSettings->resolution.height)));
    this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
    this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
    this->sidebar.setOutlineThickness(1.f);

    this->selectorRect.setSize(sf::Vector2f(this->statedata->gridSize, this->statedata->gridSize));
    this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::Green);

    this->selectorRect.setTexture(this->map->getTileSheet());
    this->selectorRect.setTextureRect(this->textureRect);

    this->textureSelector = new gui::TextureSelector(20.f, 20.f, 1000.f, 500.f, this->statedata->gridSize, this->map->getTileSheet(), this->font, "X");
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
        this->map->saveToFile("map.json");
    }

    if (this->pmenu->isButtonPressed("LOAD"))
    {
        this->map->loadFromFile("map.json");
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
                this->map->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect, this->collision, this->tileType);
            }
            else
            {
                this->textureRect = this->textureSelector->getTextureRect();
            }
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime())
    {
        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
        {
            if (!this->textureSelector->getActive())
            {
                this->map->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_COLLISION"))) && this->getKeyTime())
    {
        if (this->collision)
        {
            this->collision = false;
            this->selectorRect.setOutlineColor(sf::Color::Green);
        }
        else
        {
            this->collision = true;
            this->selectorRect.setOutlineColor(sf::Color::Red);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INCREASE_TYPE"))) && this->getKeyTime())
    {
        this->tileType++;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DECREASE_TYPE"))) && this->getKeyTime())
    {
        if (this->tileType > 0)
            this->tileType--;
    }
}

void EditorState::updateGui(const float &dt)
{

    this->textureSelector->update(this->mousePosWindow, dt);
    if (!this->textureSelector->getActive())
    {
        this->selectorRect.setTextureRect(this->textureRect);
        this->selectorRect.setPosition(this->mousePosGrid.x * this->statedata->gridSize, this->mousePosGrid.y * this->statedata->gridSize);
    }

    this->cursorText.setPosition(this->mousePosView.x + 100.f, this->mousePosView.y - 50.f);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y
       << "\n"
       << this->mousePosGrid.x << " " << this->mousePosGrid.y
       << "\n"
       << this->textureRect.left << " " << this->textureRect.top;
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

void EditorState::renderGui(sf::RenderTarget *target)
{
    if (!this->textureSelector->getActive())
    {
        target->setView(this->view);
        target->draw(this->selectorRect);
    }

    target->setView(this->statedata->gfxSettings->window->getDefaultView());
    this->textureSelector->render(*target);
    target->draw(this->sidebar);
    target->setView(this->view);
    target->draw(this->cursorText);
}

void EditorState::render(sf::RenderTarget *target)
{
    if (!target)
        target = this->statedata->gfxSettings->window;

    target->setView(this->view);
    this->map->render(*target);
    this->map->renderDeferred(*target);
    target->setView(this->statedata->gfxSettings->window->getDefaultView());
    this->renderButtons(target);
    this->renderGui(target);

    if (this->paused)
    {
        target->setView(this->statedata->gfxSettings->window->getDefaultView());
        this->pmenu->render(*target);
    }
}