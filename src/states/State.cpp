#include "State.hpp"

State::State(StateData* state_data)
{
    this->statedata = state_data;
    this->quit = false;
    this->paused = false;
    this->keyTime = 0.f;
    this->keyTimeMax = 20.f;
    this->gridSize = state_data->gridSize;
}

State::~State()
{
}

const bool &State::getQuit() const
{
    return this->quit;
}

void State::updateMousePosition(sf::View* view)
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->statedata->gfxSettings->window);

    if(view) {
        this->statedata->gfxSettings->window->setView(*view);
    }

    this->mousePosView = this->statedata->gfxSettings->window->mapPixelToCoords(sf::Mouse::getPosition(*this->statedata->gfxSettings->window));
    this->mousePosGrid = sf::Vector2u(
        static_cast<unsigned>(this->mousePosView.x) / static_cast<unsigned>(this->gridSize),
        static_cast<unsigned>(this->mousePosView.y) / static_cast<unsigned>(this->gridSize)
    );

    this->statedata->gfxSettings->window->setView(this->statedata->gfxSettings->window->getDefaultView());
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