#include "Game.h"

void Game::initWindow() {

    std::ifstream ifs("../src/config/window");
    sf::VideoMode window_bounds(800,600);
    std::string title = "Unknown";
    unsigned int framerate_limit = 120;
    bool vsync_enabled = false;
    if(ifs.is_open())
    {
        std::getline(ifs ,title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limit;
        ifs >> vsync_enabled;
    }

    ifs.close();

    this->window = new sf::RenderWindow(window_bounds, title);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vsync_enabled);
}

void Game::initStates() {
    // this->states.push(new GameState(this->window, &this->supportedKeys));
    this->states.push(new MainMenuState(this->window, &this->supportedKeys));
}

void Game::initKeys() {
    std::ifstream ifs("config/supported_keys");
    if(ifs.is_open())
    {
        std::string key = "";
        int key_value = 0;
        while(ifs >> key >> key_value)
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

    for(auto i : supportedKeys) {
        std::cout << i.first << " " << i.second << std::endl;
    }
}

//Constructors/Destructors
Game::Game()
{
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

void Game::updateSFMLEvent() {
    while(this->window->pollEvent(this->sfEvent))
    {
        if(this->sfEvent.type == sf::Event::Closed)
        {
            this->window->close();
        }
    }
}

void Game::run() {
    while (this->window->isOpen())
    {
       this->updateDt();
       this->update();
       this->render();
    }
}

void Game::update() {
    this->updateSFMLEvent();

    if(!this->states.empty())
    {
        this->states.top()->update(this->dt);
        if(this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    else {
        this->endApplication();
        this->window->close();
    }
}

void Game::render() {
    this->window->clear();

    //Render items in window
    if(!this->states.empty())
    {
        this->states.top()->render(this->window);
    }

    this->window->display();
}

void Game::updateDt() {
    //Update dt variable with the time between two loop
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::endApplication()
{
    std::cout << "End Game" << std::endl;
}