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
        std::cout << window_bounds.width << window_bounds.height;
        ifs >> framerate_limit;
        ifs >> vsync_enabled;
    }

    ifs.close();

    this->window = new sf::RenderWindow(window_bounds, title);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vsync_enabled);
}

//Constructors/Destructors
Game::Game()
{
    this->initWindow();
}

Game::~Game()
{
    delete this->window;
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
}

void Game::render() {
    this->window->clear();

    //Render items in window

    this->window->display();
}

void Game::updateDt() {
    //Update dt variable with the time between two loop
    this->dt = this->dtClock.restart().asSeconds();
}