#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "../State.hpp"
#include "../resource/headers.hpp"
#include "../resource/gui.hpp"

class EditorState : public State
{
private:
    sf::Font font;

    std::map<std::string, gui::Button*> buttons;

    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();
public:
    EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~EditorState();

    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = NULL);
    void render(sf::RenderTarget* target = NULL);

};

#endif