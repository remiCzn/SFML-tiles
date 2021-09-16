#ifndef STATE_H
#define STATE_H

#include "entities/Player.hpp"

class State
{
protected:
    std::stack<State *> *states;

    sf::RenderWindow *window;
    std::map<std::string, int> *supportedKeys;
    std::map<std::string, int> keybinds;

    std::map<std::string, sf::Texture> textures;

    bool quit;

    bool paused;
    bool lastPauseKeyStatus = false;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    float keyTime;
    float keyTimeMax;

    virtual void initKeybinds() = 0;

public:
    State(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    virtual ~State();

    const bool &getQuit() const;

    void endState();

    void pauseState();
    void unpauseState();

    virtual void updateInput(const float &dt) = 0;
    virtual void updateMousePosition();
    virtual void update(const float &dt) = 0;
    virtual void render(sf::RenderTarget *target = nullptr) = 0;

    const bool getKeyTime();
    void updateKeyTime(const float& dt);
};
#endif