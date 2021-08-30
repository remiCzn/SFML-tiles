#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "../resource/Button.h"

class MainMenuState : public State
{
private:
    sf::RectangleShape background;
    sf::Font menuFont;

    std::map<std::string, Button *> buttons;

    void initFonts();
    void initKeybinds();
    void initButtons();
public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string,int>* supportedKeys);
    virtual ~MainMenuState();

    void endState();
    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    void renderButtons(sf::RenderTarget* target = nullptr);
};

#endif