#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../State.h"

class GameState : public State
{
private:
    /* data */
public:
    GameState(sf::RenderWindow* window);
    virtual ~GameState();

    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    void endState();
};
#endif