#include "Game.hpp"

void Game::initGraphicSettings() {
    this->gfxSettings.loadFromFile("./config/window");
}

void Game::initWindow()
{
    if (this->gfxSettings.fullscreen)
        this->window = new sf::RenderWindow(
            this->gfxSettings.resolution, 
            this->gfxSettings.title, 
            sf::Style::Fullscreen, 
            this->gfxSettings.contextSettings
        );
    else
        this->window = new sf::RenderWindow(
            this->gfxSettings.resolution, 
            this->gfxSettings.title, 
            sf::Style::Titlebar | sf::Style::Close, 
            this->gfxSettings.contextSettings
        );

    this->window->setFramerateLimit(this->gfxSettings.framerateLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::initVariables()
{
    this->window = NULL;
    this->dt = 0.f;
}

void Game::initStates()
{
    // this->states.push(new GameState(this->window, &this->supportedKeys, &this->states));
    this->states.push(new MainMenuState(this->window, this->gfxSettings, &this->supportedKeys, &this->states));
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
    this->initStates();
}

Game::~Game()
{
    delete this->window;
    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

void Game::updateSFMLEvent()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
        {
            this->window->close();
        }
    }
}

void Game::run()
{
    while (this->window->isOpen())
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
        this->window->close();
    }
}

void Game::render()
{
    this->window->clear();

    //Render items in window
    if (!this->states.empty())
    {
        this->states.top()->render(this->window);
    }

    this->window->display();
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