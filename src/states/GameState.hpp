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
    sf::View view;
    sf::Font* font;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    Player* player;
    TileMap* map;

    void initKeybinds();
    void initTextures();
    void initPlayer();
    void initFonts();
    void initPauseMenu();
    void initTileMap();
    void initView();
    void initDeferredRender();


    void updatePauseMenuButtons();

public:
    GameState(StateData* statedata);
    virtual ~GameState();

    void updateView();
    void updatePlayer(const float &dt);
    void update(const float &dt);
    void updateInput(const float& dt);
    void updateTileMap(const float& dt);
    void render(sf::RenderTarget *target = nullptr);
};
#endif