#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.hpp"
#include "EditorState.hpp"
#include "SettingsState.hpp"
#include "../gui/gui.hpp"
#include "../headers/headers.hpp"

class MainMenuState : public State
{
private:
    sf::RectangleShape background;
    sf::Font menuFont;

    sf::Text title;

    std::map<std::string, gui::Button *> buttons;

    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();
    void initTitle();

public:
    MainMenuState(StateData *stateData);
    virtual ~MainMenuState();

    void updateInput(const float &dt);
    void updateButtons();
    void update(const float &dt);
    void render(sf::RenderTarget *target = nullptr);
    void renderButtons(sf::RenderTarget *target = nullptr);
};

#endif