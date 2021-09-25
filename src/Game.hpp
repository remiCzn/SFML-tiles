#ifndef GAME_H
#define GAME_H

#include "states/MainMenuState.hpp"
#include "./resource/GraphicSettings.hpp"

class Game
{
private:
    //Variables
    sf::RenderWindow *window;
    sf::Event sfEvent;
    GraphicSettings gfxSettings;

    sf::Clock dtClock;
    float dt;

    std::stack<State *> states;
    std::map<std::string, int> supportedKeys;

    //Init
    void initVariables();
    void initWindow();
    void initStates();
    void initKeys();
    void initGraphicSettings();

public:
    Game();
    virtual ~Game();

    void endApplication();

    void updateDt();
    void updateSFMLEvent();
    void update();

    void render();

    void run();
};

#endif