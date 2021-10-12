#ifndef GRAPHICS_SETTINGS_H
#define GRAPHICS_SETTINGS_H

#include "../headers/headers.hpp"

class GraphicSettings
{
public:
    GraphicSettings();
    virtual ~GraphicSettings();

    sf::RenderWindow* window;

    std::string title;
    sf::VideoMode resolution;
    bool fullscreen;
    bool verticalSync;
    unsigned framerateLimit;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;

    void saveToFile(const std::string path);
    void loadFromFile(const std::string path);

    void setFullscreen(bool value);
    void initWindow();
};

#endif