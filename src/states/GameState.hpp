#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../State.hpp"
#include "../PauseMenu.hpp"

class GameState : public State
{
private:
    PauseMenu pmenu;

    Player* player;
    void initKeybinds();
    void initTextures();
    void initPlayer();

public:
    GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    virtual ~GameState();

    void updateInput(const float &dt);
    void update(const float &dt);
    void render(sf::RenderTarget *target = nullptr);
};
#endif