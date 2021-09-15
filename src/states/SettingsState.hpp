#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include "../State.hpp"
#include "../resource/Button.hpp"

class SettingsState : public State
{
private:
    sf::Texture bgTexture;
    sf::RectangleShape bg;
    sf::Font font;

    std::map<std::string, Button*> buttons;

    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();
public:
    SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~SettingsState();

    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target);
    void render(sf::RenderTarget* target = NULL);
};

#endif