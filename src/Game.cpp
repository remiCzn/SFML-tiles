#include "Game.hpp"

void Game::initGraphicSettings() {
    this->gfxSettings.loadFromFile("./config/window.json");
}

void Game::initWindow()
{
    this->gfxSettings.initWindow();
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
        this->states.top()->update(this->dt);
        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
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

    this->gfxSettings.window->display();
}

void Game::updateDt()
{
    //Update dt variable with the time between two loop
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::endApplication()
{
    std::cout << "End Game" << std::endl;
}