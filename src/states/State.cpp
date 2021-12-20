#include "State.hpp"

void State::initView()
{
    this->view.setSize(sf::Vector2f(
        static_cast<float>(this->statedata->gfxSettings->resolution.width),
        static_cast<float>(this->statedata->gfxSettings->resolution.height))
    );

    this->view.setCenter(sf::Vector2f(
        this->statedata->gfxSettings->resolution.width / 2.f,
        this->statedata->gfxSettings->resolution.height / 2.f));
}

State::State(StateData* state_data)
{
    this->statedata = state_data;
    this->quit = false;
    this->paused = false;
    this->keyTime = 0.f;
    this->keyTimeMax = 20.f;
    this->gridSize = state_data->gridSize;

    this->initView();
}

State::~State()
{
}

const bool &State::getQuit() const
{
    return this->quit;
}

void State::updateMousePosition(sf::View *view)
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->statedata->gfxSettings->window);

    if (view)
    {
        this->statedata->gfxSettings->window->setView(*view);
    }

    this->mousePosView = this->statedata->gfxSettings->window->mapPixelToCoords(sf::Mouse::getPosition(*this->statedata->gfxSettings->window));
    this->mousePosGrid = sf::Vector2u(
        static_cast<unsigned>(this->mousePosView.x) / static_cast<unsigned>(this->gridSize),
        static_cast<unsigned>(this->mousePosView.y) / static_cast<unsigned>(this->gridSize));
    this->mousePosGridScaled = sf::Vector2u(
        this->mousePosGrid.x + static_cast<unsigned>(this->view.getCenter().x - this->view.getSize().x/2.f) / static_cast<unsigned>(gridSize),
        this->mousePosGrid.y + static_cast<unsigned>(this->view.getCenter().y - this->view.getSize().y / 2.f) / static_cast<unsigned>(gridSize)
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
    if (this->keyTime >= this->keyTimeMax)
    {
        this->keyTime = 0.f;
        return true;
    }
    return false;
}

void State::updateKeyTime(const float &dt)
{
    if (this->keyTime < this->keyTimeMax)
        this->keyTime += 100.f * dt;
}