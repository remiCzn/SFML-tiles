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
    this->bg.setFillColor(sf::Color::Black);
    //this->bg.setTexture(&this->bgTexture);
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
    float width = 250.f;
    float x = this->window->getSize().x / 2.f - width / 2.f;
    
    this->buttons["EXIT_STATE"] = new gui::Button(
        x, 500, 250, 50,
        "Quit", &this->font, 36);
}

void SettingsState::initTitle()
{
    this->menuText.setString("SETTINGS");
    this->menuText.setCharacterSize(48);
    this->menuText.setFont(this->font);
    this->menuText.setPosition(
        sf::Vector2f(
            this->window->getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2,
            50.f
        )
    );
}

SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
    : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
    this->initTitle();
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
    target->draw(this->menuText);

}