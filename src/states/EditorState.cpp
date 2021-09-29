#include "EditorState.hpp"

EditorState::EditorState(StateData* stateData)
    : State(stateData)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initPauseMenu();
    this->initButtons();
    this->initGui();
    this->initTileMap();
}

EditorState::~EditorState()
{
    for(auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }

    delete this->pmenu;
    delete this->map;
}

//Initialization
void EditorState::initVariables()
{
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

void EditorState::initPauseMenu()
{
    this->pmenu = new PauseMenu(*this->statedata->window, &this->font);

    this->pmenu->addButton("QUIT", 500.f, "Quit");
}

void EditorState::initTileMap()
{
    this->map = new TileMap(this->statedata->gridSize, 10, 10);
}

void EditorState::initGui()
{
    this->selectorRect.setSize(sf::Vector2f(this->statedata->gridSize, this->statedata->gridSize));
    this->selectorRect.setFillColor(sf::Color::Transparent);
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::Green);
}

//Update
void EditorState::updateInput(const float& dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("PAUSE"))))
    {
        if(this->lastPauseKeyStatus == false && this->getKeyTime())
        {
            if(this->paused)
            {   
                this->unpauseState();
            }
            else {
                this->pauseState();
            }
        }
        this->lastPauseKeyStatus = true;
    }
    else {
        this->lastPauseKeyStatus = false;
    }
}

void EditorState::updateButtons()
{
    for(auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
}

void EditorState::update(const float& dt)
{
    this->updateMousePosition();
    this->updateKeyTime(dt);
    this->updateInput(dt);
    if(!this->paused)
    {
        this->updateButtons();
        this->updateGui();
        this->updateEditorInput(dt);
    }
    else {
        this->pmenu->update(this->mousePosView);
        this->updatePauseMenu();
    }
    
}

void EditorState::updatePauseMenu()
{
    if(this->pmenu->isButtonPressed("QUIT"))
    {
        this->endState();
    }
}

void EditorState::updateEditorInput(const float& dt)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime())
    {
        this->map->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime())
    {
        this->map->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
    }
}

void EditorState::updateGui() {
    this->selectorRect.setPosition(this->mousePosGrid.x * this->statedata->gridSize, this->mousePosGrid.y * this->statedata->gridSize);
}

//Render
void EditorState::renderButtons(sf::RenderTarget* target)
{
    for(auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void EditorState::renderGui(sf::RenderTarget* target)
{
    target->draw(this->selectorRect);
}

void EditorState::render(sf::RenderTarget* target)
{
    if(!target)
        target = this->statedata->window;

    this->renderButtons(target);
    this->renderGui(target);
    this->map->render(*target);

    if(this->paused)
    {
        this->pmenu->render(*target);
    }

    sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}