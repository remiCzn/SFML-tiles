#ifndef STATE_H
#define STATE_H

#include "../headers/headers.hpp"
#include "../resource/GraphicSettings.hpp"

class State;

class StateData
{
public:
    StateData(){};

    float gridSize;
    GraphicSettings *gfxSettings;
    std::map<std::string, int> *supportedKeys;
    std::stack<State *> *states;
    bool debugMode;
};

class State
{
protected:
    StateData *statedata;

    std::map<std::string, int> keybinds;

    std::map<std::string, sf::Texture> textures;

    sf::View view;

    bool quit;

    bool paused;
    bool lastPauseKeyStatus = false;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2i mousePosGrid;
    sf::Vector2i mousePosGridScaled;

    float keyTime;
    float keyTimeMax;
    float gridSize;

    virtual void initKeybinds() = 0;
    void initView();

public:
    State(StateData *state_data);
    virtual ~State();

    const bool &getQuit() const;

    void endState();

    void pauseState();
    void unpauseState();

    virtual void updateInput(const float &dt) = 0;
    virtual void updateMousePosition(sf::View *view = NULL);
    virtual void update(const float &dt) = 0;
    virtual void render(sf::RenderTarget *target = nullptr) = 0;

    const bool getKeyTime();
    void updateKeyTime(const float &dt);
};
#endif