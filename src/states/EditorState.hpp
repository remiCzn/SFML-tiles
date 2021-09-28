#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "./State.hpp"
#include "../headers/headers.hpp"
#include "../resource/gui.hpp"
#include "../gui/PauseMenu.hpp"
#include "../tile/TileMap.hpp"

class EditorState : public State
{
private:
    sf::Font font;
    PauseMenu* pmenu;

    TileMap* map;

    std::map<std::string, gui::Button*> buttons;

    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initPauseMenu();
    void initButtons();
    void initTileMap();
public:
    EditorState(StateData* stateData);
    virtual ~EditorState();

    void updateInput(const float& dt);
    void updateButtons();
    void updatePauseMenu();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = NULL);
    void render(sf::RenderTarget* target = NULL);

};

#endif