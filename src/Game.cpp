#include "Game.hpp"

void Game::initWindow()
{

    std::ifstream ifs("./config/window");
    this->videoModes = sf::VideoMode::getFullscreenModes();

    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    bool fullscreen = false;
    std::string title = "Unknown";
    unsigned int framerate_limit = 120;
    bool vsync_enabled = false;
    unsigned antialising_level = 0;

    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> fullscreen;
        ifs >> framerate_limit;
        ifs >> vsync_enabled;
        ifs >> antialising_level;
    }

    ifs.close();

    this->windowSettings.antialiasingLevel = antialising_level;
    this->fullscreen = fullscreen;

    if (this->fullscreen)
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, this->windowSettings);
    else
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, this->windowSettings);

    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vsync_enabled);
}

void Game::initVariables()
{
    this->window = NULL;
    this->fullscreen = false;
    this->dt = 0.f;
}

void Game::initStates()
{
    this->states.push(new GameState(this->window, &this->supportedKeys, &this->states));
    // this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
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

    //is now in the config file "supported_keys"
    // this->supportedKeys["Escape"] = sf::Keyboard::Escape;
    // this->supportedKeys["Q"] = sf::Keyboard::Q;
    // this->supportedKeys["D"] = sf::Keyboard::D;
    // this->supportedKeys["Z"] = sf::Keyboard::Z;
    // this->supportedKeys["S"] = sf::Keyboard::S;

    for (auto i : supportedKeys)
    {
        std::cout << i.first << " " << i.second << std::endl;
    }
}

//Constructors/Destructors
Game::Game()
{
    this->initVariables();
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