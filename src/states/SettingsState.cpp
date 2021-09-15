#include "SettingsState.hpp"

void SettingsState::initVariables(){

}

void SettingsState::initBackground()
{
    this->bg.setSize(
        sf::Vector2f(
            static_cast<float>(this->window->getSize().x),
            static_cast<float>(this->window->getSize().y)
        )
    );
    if(!this->bgTexture.loadFromFile("images/background/background.png"))
    {
        throw "ERROR::SETTINGS_STATE::Failed to load bg texture";
    }

    this->bg.setTexture(&this->bgTexture);
}

void SettingsState::initFonts()
{
    if(!this->font.loadFromFile("fonts/FreeSans.ttf"))
    {
        throw("ERROR::SETTINGS_STATE::Failed to load font");
    }
}

void SettingsState::initKeybinds()
{
    std::ifstream ifs("config/settingsstate_keybinds");
    if (ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2)
        {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void SettingsState::initButtons()
{
    this->buttons["EXIT_STATE"] = new Button(
        300, 500, 250, 50,
        "Quit", &this->font, 50,
        sf::Color(100,100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
        sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50));

}

SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
    : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
}

SettingsState::~SettingsState()
{
    for(auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

void SettingsState::updateInput(const float& dt)
{

}

void SettingsState::updateButtons()
{
    for(auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
    if(this->buttons["EXIT_STATE"]->isPressed())
    {
        this->endState();
    }
}

void SettingsState::update(const float& dt)
{
    this->updateMousePosition();
    this->updateInput(dt);
    this->updateButtons();
}

void SettingsState::renderButtons(sf::RenderTarget* target)
{
    for(auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void SettingsState::render(sf::RenderTarget* target)
{
    if(!target)
    {
        target = this->window;
    }

    target->draw(this->bg);
    this->renderButtons(target);

}