#ifndef GAME_H
#define GAME_H

#include "State.h"

class Game
{
private:
    //Variables
    sf::RenderWindow *window;
    sf::Event sfEvent;

    sf::Clock dtClock;
    float dt;

    //Init
    void initWindow();
public:
    Game();
    virtual ~Game();

    void updateDt();
    void updateSFMLEvent();
    void update();
    void render();
    void run();
};

#endif