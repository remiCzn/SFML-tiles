#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "./State.hpp"
#include "../gui/PauseMenu.hpp"
#include "../headers/headers.hpp"
#include "../entities/Player.hpp"
#include "../tile/TileMap.hpp"
#include "../gui/PlayerGUI.hpp"

class GameState : public State
{
private:
    PauseMenu *pmenu;
    sf::Font *font;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    Player *player;
    PlayerGUI *playerGui;
    TileMap *map;

    void initKeybinds();
    void initTextures();
    void initPlayer();
    void initPlayerGui();
    void initFonts();
    void initPauseMenu();
    void initTileMap();
    void initDeferredRender();

    void updatePauseMenuButtons();

public:
    GameState(StateData *statedata);
    virtual ~GameState();

    void updateView();
    void updatePlayer(const float &dt);
    void update(const float &dt);
    void updateInput(const float &dt);
    void updatePlayerGUI(const float &dt);
    void updateTileMap(const float &dt);
    void render(sf::RenderTarget *target = nullptr);
};
#endif