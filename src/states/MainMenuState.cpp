#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string,int>* supportedKeys) 
    : State(window, supportedKeys)
{
    this->initFonts();
    this->initKeybinds();
    this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::initFonts() {
    if(!this->menuFont.loadFromFile("fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::Could not load font");
    }
}

void MainMenuState::initKeybinds() {
    std::ifstream ifs("config/gamestate_keybinds");
    if(ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";
        while(ifs >> key >> key2)
        {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void MainMenuState::update(const float& dt)
{
    this->updateInput(dt);
    this->updateMousePosition();
}

void MainMenuState::updateInput(const float& dt)
{
    this->checkForQuit();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
    {

    }
}

void MainMenuState::render(sf::RenderTarget* target)
{
    if(!target)
        target = this->window;

    target->draw(this->background);
}

void MainMenuState::endState() {
    std::cout << "END MainMenuState" << std::endl;
}