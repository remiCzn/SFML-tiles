#include "State.hpp"

State::State(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
{
    this->states = states;
    this->window = window;
    this->supportedKeys = supportedKeys;
    this->quit = false;
    this->paused = false;
    this->keyTime = 0.f;
    this->keyTimeMax = 20.f;
}

State::~State()
{
}

const bool &State::getQuit() const
{
    return this->quit;
}

void State::updateMousePosition()
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::endState()
{
    this->quit = true;
}

void State::pauseState()
{
    this->paused = true;
}   

void State::unpauseState()
{
    this->paused = false;
}

const bool State::getKeyTime()
{
    if(this->keyTime >= this->keyTimeMax)
    {
        this->keyTime = 0.f;
        return true;
    }
    return false;
}

void State::updateKeyTime(const float& dt)
{
    if(this->keyTime < this->keyTimeMax)
        this->keyTime += 100.f * dt;
}