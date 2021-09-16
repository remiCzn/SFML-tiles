#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../State.hpp"
#include "../gui/PauseMenu.hpp"
#include "../resource/headers.hpp"
#include "entities/Player.hpp"

class GameState : public State
{
private:
    PauseMenu* pmenu;

    sf::Font* font;

    Player* player;
    void initKeybinds();
    void initTextures();
    void initPlayer();
    void initFonts();
    void initPauseMenu();

    void updatePauseMenuButtons();

public:
    GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    virtual ~GameState();

    void updatePlayer(const float &dt);
    void update(const float &dt);
    void updateInput(const float& dt);
    void render(sf::RenderTarget *target = nullptr);
};
#endif