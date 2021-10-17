#include "GameState.hpp"

GameState::GameState(StateData* stateData)
    : State(stateData)
{
    this->initKeybinds();
    this->initFonts();
    this->initView();
    this->initTextures();
    this->initPauseMenu();
    this->initPlayer();
    this->initTileMap();
}

GameState::~GameState()
{
    delete this->pmenu;
    delete this->player;
    delete this->font;
    delete this->map;
}

void GameState::initKeybinds()
{
    std::ifstream ifs("config/gamestate_keybinds");
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

void GameState::initTextures()
{
    if(!this->textures["PLAYER_IDLE"].loadFromFile("images/character/player_sheet.png"))
    {
        throw("ERROR::GAME_STATE::Could not load down idle sprite");
    }
}

void GameState::initFonts()
{
    this->font = new sf::Font();
    if(!this->font->loadFromFile("fonts/FreeSans.ttf"))
    {
        throw("ERROR::GAME_STATE::Could not load font for GUI");
    }
}

void GameState::initView()
{
    this->view.setSize(
        this->statedata->gfxSettings->resolution.width,
        this->statedata->gfxSettings->resolution.height
    );

    this->view.setCenter(
        this->statedata->gfxSettings->resolution.width / 2.f,
        this->statedata->gfxSettings->resolution.height / 2.f
    );
}

void GameState::initPauseMenu()
{
    this->pmenu = new PauseMenu(*this->statedata->gfxSettings->window, this->font);
    this->pmenu->addButton("QUIT", 500.f, "Quit");
    this->pmenu->addButton("CONTINUE", 200.f, "Continue");
}

void GameState::initPlayer() {
    this->player = new Player(0,0,&this->textures["PLAYER_IDLE"]);
}

void GameState::initTileMap() {
    this->map = new TileMap(this->statedata->gridSize, 10, 10, "images/Tiles/tilesheet.png");
    this->map->loadFromFile("map.json");
}

void GameState::update(const float &dt)
{
    this->updateMousePosition();
    this->updateKeyTime(dt);
    this->updateInput(dt);
    if(this->paused)
    {
        this->pmenu->update(this->mousePosWindow);
        this->updatePauseMenuButtons();
    }
    else {
        this->updateView();
        this->updatePlayer(dt);
        this->player->update(dt);
    }
}

void GameState::updateView() {
    this->view.setCenter(
        this->player->getPosition().x + 64.f,
        this->player->getPosition().y + 64.f
    );
}

void GameState::updatePlayer(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
    {
        this->player->move(dt, -1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
    {
        this->player->move(dt, 1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
    {
        this->player->move(dt, 0.f, -1.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
    {
        this->player->move(dt, 0.f, 1.f);
    }
}

void GameState::updateInput(const float& dt)
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

void GameState::updatePauseMenuButtons() {
    if(this->pmenu->isButtonPressed("QUIT"))
    {
        this->endState();
    }
    if(this->pmenu->isButtonPressed("CONTINUE"))
    {
        this->unpauseState();
    }
}


void GameState::render(sf::RenderTarget *target)
{
    if (!target)
        target = this->statedata->gfxSettings->window;

    target->setView(this->view);
    this->map->render(*target);
    
    this->player->render(target);
    if(this->paused)
    {
        target->setView(this->statedata->gfxSettings->window->getDefaultView());
        this->pmenu->render(*target);
    }
}