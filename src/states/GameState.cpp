#include "GameState.h"

GameState::GameState(sf::RenderWindow* window) : State(window)
{
}

GameState::~GameState()
{
}

void GameState::update(const float& dt)
{
    std::cout << "Hello from Gamestate!!" << std::endl;
}

void GameState::render(sf::RenderTarget* window)
{

}

void GameState::endState() {

}
