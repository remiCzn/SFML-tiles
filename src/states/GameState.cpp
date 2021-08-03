#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::map<std::string,int>* supportedKeys) 
    : State(window, supportedKeys)
{
    this->initKeybinds();
}

GameState::~GameState()
{
}

void GameState::initKeybinds() {
    this->keybinds.emplace("MOVE_LEFT", this->supportedKeys->at("Q"));
    this->keybinds.emplace("MOVE_RIGHT", this->supportedKeys->at("D"));
    this->keybinds.emplace("MOVE_UP", this->supportedKeys->at("Z"));
    this->keybinds.emplace("MOVE_DOWN", this->supportedKeys->at("S"));
}

void GameState::update(const float& dt)
{
    this->updateInput(dt);
    this->player.update(dt);
}

void GameState::updateInput(const float& dt)
{
    this->checkForQuit();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
    {
        this->player.move(dt, -1.f, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
    {
        this->player.move(dt, 1.f, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
    {
        this->player.move(dt, 0.f, -1.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
    {
        this->player.move(dt, 0.f, 1.f);
    }
}

void GameState::render(sf::RenderTarget* target)
{
    if(!target)
        target = this->window;
    this->player.render(target);
}

void GameState::endState() {
    std::cout << "END gamestate" << std::endl;
}