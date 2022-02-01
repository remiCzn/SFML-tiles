#include "GameState.hpp"

GameState::GameState(StateData *stateData)
    : State(stateData)
{
    this->initDeferredRender();
    this->initKeybinds();
    this->initFonts();
    this->initTextures();
    this->initPauseMenu();
    this->initShaders();
    this->initPlayer();
    this->initPlayerGui();
    this->initTileMap();
}

GameState::~GameState()
{
    delete this->pmenu;
    delete this->player;
    delete this->font;
    delete this->map;
    delete this->playerGui;
}

void GameState::initPlayerGui()
{
    this->playerGui = new PlayerGUI(this->player);
}

void GameState::initShaders()
{
    /*if (!sf::Shader::isAvailable() || !this->core_shader.loadFromFile("src/resource/fragment_shader.frag", sf::Shader::Fragment))
    {
        std::cout << "ERROR::GAMESTATE::COULD NOT LOAD SHADER" << std::endl;
    }*/
}

void GameState::initKeybinds()
{
    std::ifstream ifs("src/config/gamestate_keybinds");
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
    if (!this->textures["PLAYER_IDLE"].loadFromFile("src/images/character/player_sheet.png"))
    {
        throw("ERROR::GAME_STATE::Could not load down idle sprite");
    }
}

void GameState::initFonts()
{
    this->font = new sf::Font();
    if (!this->font->loadFromFile("src/fonts/FreeSans.ttf"))
    {
        throw("ERROR::GAME_STATE::Could not load font for GUI");
    }
}

void GameState::initPauseMenu()
{
    this->pmenu = new PauseMenu(*this->statedata->gfxSettings->window, this->font);
    this->pmenu->addButton("QUIT", 500.f, "Quit");
    this->pmenu->addButton("CONTINUE", 200.f, "Continue");
}

void GameState::initPlayer()
{
    this->player = new Player(8 * this->statedata->gridSize, 24 * this->statedata->gridSize, &this->textures["PLAYER_IDLE"]);
}

void GameState::initTileMap()
{
    this->map = new TileMap(this->statedata->gridSize, 5, 16, "src/images/Tiles/Stonex20.png");
    this->map->loadFromFile("src/map.json");
}

void GameState::initDeferredRender()
{
    this->renderTexture.create(
        this->statedata->gfxSettings->resolution.width,
        this->statedata->gfxSettings->resolution.height);

    this->renderSprite.setTexture(this->renderTexture.getTexture());
    this->renderSprite.setTextureRect(
        sf::IntRect(
            0, 0,
            this->statedata->gfxSettings->resolution.width,
            this->statedata->gfxSettings->resolution.height));
    this->shaderTexture.create(
        this->statedata->gfxSettings->resolution.width,
        this->statedata->gfxSettings->resolution.height);

    this->shaderSprite.setTexture(this->shaderTexture.getTexture());
    this->shaderSprite.setTextureRect(
        sf::IntRect(
            0, 0,
            this->statedata->gfxSettings->resolution.width,
            this->statedata->gfxSettings->resolution.height));
}

void GameState::update(const float &dt)
{
    this->updateMousePosition();
    this->updateKeyTime(dt);
    this->updateInput(dt);
    if (this->paused)
    {
        this->pmenu->update(this->mousePosWindow);
        this->updatePauseMenuButtons();
    }
    else
    {
        this->updateView();
        this->updatePlayer(dt);
        this->updateTileMap(dt);
        this->player->update(dt);
        this->updatePlayerGUI(dt);
    }
}

void GameState::updateView()
{
    this->view.setCenter(
        std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->statedata->gfxSettings->resolution.width / 2)) / 10.f),
        std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->statedata->gfxSettings->resolution.height / 2)) / 10.f));

    if (this->view.getCenter().x - this->view.getSize().x / 2.f < -this->map->getWorldSize()) {
        this->view.setCenter(
            this->view.getSize().x / 2.f - this->map->getWorldSize(),
            this->view.getCenter().y
        );
    }
    else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->map->getWorldSize()) {
        this->view.setCenter(
            - this->view.getSize().x / 2.f + this->map->getWorldSize(),
            this->view.getCenter().y
        );
    }

    if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->map->getWorldSize()) {
        this->view.setCenter(
            this->view.getCenter().x,
            -this->view.getSize().y / 2.f + this->map->getWorldSize()
        );
    } else if (this->view.getCenter().y - this->view.getSize().y / 2.f < -this->map->getWorldSize()) {
        this->view.setCenter(
            this->view.getCenter().x,
            this->view.getSize().y / 2.f - this->map->getWorldSize()
        );
    }

    this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->statedata->gridSize);
    this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->statedata->gridSize);
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

void GameState::updatePlayerGUI(const float &dt)
{
    this->playerGui->update(dt);
}

void GameState::updateInput(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("PAUSE"))))
    {
        if (this->lastPauseKeyStatus == false && this->getKeyTime())
        {
            if (this->paused)
            {
                this->unpauseState();
            }
            else
            {
                this->pauseState();
            }
        }
        this->lastPauseKeyStatus = true;
    }
    else
    {
        this->lastPauseKeyStatus = false;
    }
}

void GameState::updatePauseMenuButtons()
{
    if (this->pmenu->isButtonPressed("QUIT"))
    {
        this->endState();
    }
    if (this->pmenu->isButtonPressed("CONTINUE"))
    {
        this->unpauseState();
    }
}

void GameState::updateTileMap(const float &dt)
{
    this->map->update();
    this->map->updateCollision(this->player, dt);
}

void GameState::render(sf::RenderTarget *target)
{
    if (!target)
        target = this->statedata->gfxSettings->window;

    this->core_shader.setUniform("winSize", sf::Vector2f(
        static_cast<float>(this->statedata->gfxSettings->window->getSize().x),
        static_cast<float>(this->statedata->gfxSettings->window->getSize().y))
    );
    this->core_shader.setUniform("hasTexture", true);
    this->core_shader.setUniform("light", sf::Vector3f(
        this->player->getPosition().x - this->view.getCenter().x + this->view.getSize().x / 2.f,
        this->player->getPosition().y - this->view.getCenter().y + this->view.getSize().y / 2.f,
        this->statedata->gfxSettings->window->getSize().y / 2.f)
    );

    this->renderTexture.clear();
    this->shaderTexture.clear();
    this->shaderTexture.setView(this->view);
    this->map->render(
        this->shaderTexture,
        this->statedata->debugMode,
        sf::Vector2i(this->player->getPosition() / this->gridSize),
        this->viewGridPosition);

    this->player->render(this->shaderTexture, this->statedata->debugMode);

    this->map->renderDeferred(this->shaderTexture, this->statedata->debugMode);

    this->shaderTexture.display();
    this->renderTexture.draw(this->shaderSprite, &this->core_shader);

    this->renderTexture.setView(this->statedata->gfxSettings->window->getDefaultView());
    this->playerGui->render(this->renderTexture);

    if (this->paused)
    {
        this->pmenu->render(this->renderTexture);
    }
    
    this->renderTexture.display();
    target->draw(this->renderSprite);
}