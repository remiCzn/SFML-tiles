#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../State.h"

class GameState : public State
{
private:
    Entity player;
public:
    GameState(sf::RenderWindow* window);
    virtual ~GameState();

    void endState();
    void updateKeyBinds(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};
#endif