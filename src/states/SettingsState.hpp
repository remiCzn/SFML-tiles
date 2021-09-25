#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include "./State.hpp"
#include "../resource/GraphicSettings.hpp"
#include "../resource/gui.hpp"
#include "../headers/headers.hpp"

class SettingsState : public State
{
private:
    GraphicSettings& gfxSettings;
    sf::Texture bgTexture;
    sf::RectangleShape bg;
    sf::Font font;

    sf::Text menuText;

    sf::Text optionsText;
    std::vector<sf::VideoMode> modes;

    std::map<std::string, gui::DropDownList*> ddls;
    std::map<std::string, gui::Button*> buttons;

    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initGui();
    void initTitle();
public:
    SettingsState(sf::RenderWindow* window, GraphicSettings& gfxSettings, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~SettingsState();

    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);
    void renderGui(sf::RenderTarget* target);
    void render(sf::RenderTarget* target = NULL);
};

#endif