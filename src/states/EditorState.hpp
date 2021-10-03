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
    sf::Text cursorText;
    PauseMenu* pmenu;

    TileMap* map;

    sf::RectangleShape sidebar;

    sf::IntRect textureRect;
    sf::RectangleShape selectorRect;

    gui::TextureSelector* textureSelector;

    std::map<std::string, gui::Button*> buttons;

    void initVariables();
    void initBackground();
    void initFonts();
    void initText();
    void initKeybinds();
    void initPauseMenu();
    void initButtons();
    void initGui();
    void initTileMap();
public:
    EditorState(StateData* stateData);
    virtual ~EditorState();

    void updateInput(const float& dt);
    void updateEditorInput(const float& dt);
    void updateButtons();
    void updateGui(const float& dt);
    void updatePauseMenu();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = NULL);
    void renderGui(sf::RenderTarget* target = NULL);
    void render(sf::RenderTarget* target = NULL);

};

#endif