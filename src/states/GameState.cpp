#include "GameState.h"

GameState::GameState(sf::RenderWindow* window) : State(window)
{
}

GameState::~GameState()
{
}

void GameState::update(const float& dt)
{
    this->updateKeyBinds(dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        std::cout << "A" << std::endl;
    }
}

void GameState::updateKeyBinds(const float& dt)
{
    this->checkForQuit();
}

void GameState::render(sf::RenderTarget* window)
{

}

void GameState::endState() {
    std::cout << "END gamestate" << std::endl;
}