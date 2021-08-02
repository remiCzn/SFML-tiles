#include "Game.h"

void Game::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(800,600), "TilesRPG");
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