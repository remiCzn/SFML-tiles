#include "Game.hpp"

void Game::initGraphicSettings() {
    this->gfxSettings.loadFromFile("./config/window.json");
}

void Game::initWindow()
{
    this->gfxSettings.initWindow();
    if(!this->dtFont.loadFromFile("./fonts/Dosis-Light.ttf"))
    {
        std::cout << "GAME:FONT NOT LOADED" << std::endl;
    }
    this->dtRendered.setFont(this->dtFont);
    this->dtRendered.setString("0");
    this->dtRendered.setCharacterSize(50);
    this->dtRendered.setPosition(0,0);
    this->dtRendered.setFillColor(sf::Color::White);
}

void Game::initVariables()
{
    this->dt = 0.f;
    this->gridSize = 100.f;
}

void Game::initStateData()
{
    this->stateData.gfxSettings = &this->gfxSettings;
    this->stateData.gridSize = this->gridSize;
    this->stateData.states = &this->states;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.debugMode = false;
}

void Game::initStates()
{
    this->states.push(new MainMenuState(&stateData));
    // this->states.push(new EditorState(&stateData));
}

void Game::initKeys()
{
    std::ifstream ifs("config/supported_keys");
    if (ifs.is_open())
    {
        std::string key = "";
        int key_value = 0;
        while (ifs >> key >> key_value)
        {
            this->supportedKeys[key] = key_value;
        }
    }

    ifs.close();

    for (auto i : supportedKeys)
    {
        std::cout << i.first << " " << i.second << std::endl;
    }
}

//Constructors/Destructors
Game::Game()
{
    this->initVariables();
    this->initGraphicSettings();
    this->initWindow();
    this->initKeys();
    this->initStateData();
    this->initStates();
}

Game::~Game()
{
    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

void Game::updateSFMLEvent()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) {
        if(!KeyState::getInstance()->F3) {
            this->stateData.debugMode = !this->stateData.debugMode;
            KeyState::getInstance()->F3 = true;
        }
    } else {
        KeyState::getInstance()->F3 = false;
    }

    while (this->gfxSettings.window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
        {
            this->gfxSettings.window->close();
        }
    }
}

void Game::run()
{
    while (this->gfxSettings.window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}

void Game::update()
{
    this->updateSFMLEvent();

    if (!this->states.empty())
    {
        if(this->stateData.gfxSettings->window->hasFocus())
        {
            this->states.top()->update(this->dt);
            if (this->states.top()->getQuit())
            {
                this->states.top()->endState();
                delete this->states.top();
                this->states.pop();
            }
        }
    }
    else
    {
        this->endApplication();
        this->gfxSettings.window->close();
    }
}

void Game::render()
{
    this->gfxSettings.window->clear();

    //Render items in window
    if (!this->states.empty())
    {
        this->states.top()->render(this->gfxSettings.window);
    }
    if(this->stateData.debugMode)
    {
        this->gfxSettings.window->draw(this->dtRendered);
    }
    this->gfxSettings.window->display();
}

void Game::updateDt()
{
    //Update dt variable with the time between two loop
    this->dt = this->dtClock.restart().asSeconds();
    if(this->stateData.debugMode) {
        this->dtRendered.setString(std::to_string(static_cast<int>(1 / this->dt)));
    }
}

void Game::endApplication()
{
    std::cout << "End Game" << std::endl;
}