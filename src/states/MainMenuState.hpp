#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.hpp"
#include "EditorState.hpp"
#include "SettingsState.hpp"
#include "../resource/gui.hpp"
#include "../headers/headers.hpp"

class MainMenuState : public State
{
private:
    sf::Texture bgTexture;
    sf::RectangleShape background;
    sf::Font menuFont;

    std::map<std::string, gui::Button *> buttons;

    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    virtual ~MainMenuState();

    void updateInput(const float &dt);
    void updateButtons();
    void update(const float &dt);
    void render(sf::RenderTarget *target = nullptr);
    void renderButtons(sf::RenderTarget *target = nullptr);
};

#endif