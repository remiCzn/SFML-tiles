#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "./State.hpp"
#include "../gui/PauseMenu.hpp"
#include "../headers/headers.hpp"
#include "../entities/Player.hpp"
#include "../tile/TileMap.hpp"

class GameState : public State
{
private:
    PauseMenu* pmenu;

    sf::Font* font;

    Player* player;
    TileMap* map;

    void initKeybinds();
    void initTextures();
    void initPlayer();
    void initFonts();
    void initPauseMenu();
    void initTileMap();


    void updatePauseMenuButtons();

public:
    GameState(StateData* statedata);
    virtual ~GameState();

    void updatePlayer(const float &dt);
    void update(const float &dt);
    void updateInput(const float& dt);
    void render(sf::RenderTarget *target = nullptr);
};
#endif