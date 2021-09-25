#include "SettingsState.hpp"

void SettingsState::initVariables(){
    this->modes = std::vector<sf::VideoMode>({
        sf::VideoMode(1920, 1080, 32),
        sf::VideoMode(1600,900, 32),
        sf::VideoMode(1440,810, 32),
        sf::VideoMode(1368, 768, 32),
        sf::VideoMode(1360,768, 32),
        sf::VideoMode(1280,720,32),
        sf::VideoMode(1024,576, 32),
        sf::VideoMode(960,540,32)
    });
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

void SettingsState::initGui()
{
    float width = 250.f;
    float x = this->window->getSize().x / 2.f - width / 2.f;
    
    this->buttons["EXIT_STATE"] = new gui::Button(
        x - 130, 500, 250, 50,
        "Quit", &this->font, 36);

    this->buttons["APPLY"] = new gui::Button(
        x + 130, 500, 250, 50,
        "Apply", &this->font, 36);

    std::vector<std::string> modes_str;
    for(auto &i : this->modes)
    {
        modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
    }
    this->ddls["RESOLUTION"] = new gui::DropDownList(
        x, 200.f, 200.f, 40.f, 
        &this->font, modes_str.data(), modes_str.size());
    
    this->buttons["FULLSCREEN"] = new gui::Button(
        x, 265.f, 200.f, 40.f,
        "Fullscreen", &this->font, 16.f
    );

    this->buttons["VSYNC"] = new gui::Button(
        x, 330.f, 200.f, 40.f,
        "VSync", &this->font, 16.f
    );

    this->buttons["ANTIALIASING"] = new gui::Button(
        x, 395.f, 200.f, 40.f,
        "Antialiasing", &this->font, 16.f
    );
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

    this->optionsText.setFont(this->font);
    this->optionsText.setPosition(sf::Vector2f(300.f, 200.f));
    this->optionsText.setCharacterSize(30);
    this->optionsText.setFillColor(sf::Color(255,255,255,200));

    this->optionsText.setString(
        "Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n "
    );
}

SettingsState::SettingsState(sf::RenderWindow* window, GraphicSettings& gfxSettings, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
    : State(window, supportedKeys, states), gfxSettings(gfxSettings)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initGui();
    this->initTitle();
}

SettingsState::~SettingsState()
{
    for(auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
    for(auto it = this->ddls.begin(); it != this->ddls.end(); ++it)
    {
        delete it->second;
    }
}

void SettingsState::updateInput(const float& dt)
{

}

void SettingsState::updateGui(const float& dt)
{
    for(auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
    for(auto &it : this->ddls)
    {
        it.second->update(this->mousePosView, dt);
    }

    if(this->buttons["EXIT_STATE"]->isPressed())
    {
        this->endState();
    }
    if(this->buttons["APPLY"]->isClicked())
    {
        this->gfxSettings.resolution = this->modes.at(this->ddls["RESOLUTION"]->getActiveElementId());
        this->window->create(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Titlebar | sf::Style::Close);
        this->gfxSettings.saveToFile("../config/window");
    }
}

void SettingsState::update(const float& dt)
{
    this->updateMousePosition();
    this->updateInput(dt);
    this->updateGui(dt);
}

void SettingsState::renderGui(sf::RenderTarget* target)
{
    for(auto &it : this->buttons)
    {
        it.second->render(target);
    }
    for(auto &it : this->ddls)
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
    this->renderGui(target);
    target->draw(this->menuText);
    target->draw(this->optionsText);

    // //remove later
    // sf::Text mouseText;
    // mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
    // mouseText.setFont(this->font);
    // mouseText.setColor(sf::Color::White);
    // mouseText.setCharacterSize(12);
    // std::stringstream ss;
    // ss << this->mousePosView.x << "  " << this->mousePosView.y;
    // mouseText.setString(ss.str());

    // target->draw(mouseText);

}