#ifndef GAME_H
#define GAME_H

#include "states/MainMenuState.hpp"
#include "./resource/GraphicSettings.hpp"

class Game
{
private:
    //Variables
    sf::Event sfEvent;
    GraphicSettings gfxSettings;

    StateData stateData;

    sf::Clock dtClock;
    float dt;
    float gridSize;

    std::stack<State *> states;
    std::map<std::string, int> supportedKeys;

    //Init
    void initVariables();
    void initWindow();
    void initStates();
    void initKeys();
    void initGraphicSettings();
    void initStateData();

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