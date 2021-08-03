#ifndef GAME_H
#define GAME_H

#include "states/GameState.h"

class Game
{
private:
    //Variables
    sf::RenderWindow *window;
    sf::Event sfEvent;

    sf::Clock dtClock;
    float dt;

    std::stack<State*> states;

    //Init
    void initWindow();
    void initStates();
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