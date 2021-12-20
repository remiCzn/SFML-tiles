#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "./State.hpp"
#include "../headers/headers.hpp"
#include "../gui/gui.hpp"
#include "../gui/PauseMenu.hpp"
#include "../tile/TileMap.hpp"

class EditorState : public State
{
private:
    sf::Font font;
    sf::Text cursorText;
    PauseMenu *pmenu;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    TileMap *map;

    sf::RectangleShape sidebar;

    sf::IntRect textureRect;
    sf::RectangleShape selectorRect;

    gui::TextureSelector *textureSelector;

    std::map<std::string, gui::Button *> buttons;

    bool collision;
    short tileType;

    float cameraSpeed;

    void initVariables();
    void initBackground();
    void initFonts();
    void initText();
    void initKeybinds();
    void initPauseMenu();
    void initButtons();
    void initGui();
    void initTileMap();
    void initDeferredRender();

    sf::Vector2f getViewOffset();
    sf::Vector2u getMousePosGrid();

public:
    EditorState(StateData *stateData);
    virtual ~EditorState();

    void updateInput(const float &dt);
    void updateEditorInput(const float &dt);
    void updateButtons();
    void updateGui(const float &dt);
    void updatePauseMenu();
    void update(const float &dt);
    void renderButtons(sf::RenderTarget *target = NULL);
    void renderGui();
    void render(sf::RenderTarget *target = NULL);
};

#endif