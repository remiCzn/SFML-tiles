#ifndef GAME_H
#define GAME_H

#include "states/MainMenuState.h"

class Game
{
private:
    //Variables
    sf::RenderWindow *window;
    sf::Event sfEvent;

    sf::Clock dtClock;
    float dt;

    std::stack<State*> states;
    std::map<std::string, int> supportedKeys;

    //Init
    void initWindow();
    void initStates();
    void initKeys();
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