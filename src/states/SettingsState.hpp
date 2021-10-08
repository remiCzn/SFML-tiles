#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include "./State.hpp"
#include "../resource/GraphicSettings.hpp"
#include "../resource/gui.hpp"
#include "../headers/headers.hpp"

class SettingsState : public State
{
private:
    sf::Texture bgTexture;
    sf::RectangleShape bg;
    sf::Font font;

    sf::Text menuText;

    sf::Text optionsText;
    std::vector<sf::VideoMode> modes;

    std::map<std::string, gui::DropDownList*> ddls;
    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::CheckBox*> checkBoxs;

    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initGui();
    void initTitle();
public:
    SettingsState(StateData* state_data);
    virtual ~SettingsState();

    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);
    void renderGui(sf::RenderTarget* target);
    void render(sf::RenderTarget* target = NULL);
};

#endif