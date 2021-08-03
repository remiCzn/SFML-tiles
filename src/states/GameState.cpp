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
    this->player.update(dt);
}

void GameState::updateKeyBinds(const float& dt)
{
    this->checkForQuit();
}

void GameState::render(sf::RenderTarget* target)
{
    this->player.render(target);
}

void GameState::endState() {
    std::cout << "END gamestate" << std::endl;
}