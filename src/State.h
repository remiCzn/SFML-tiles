#ifndef STATE_H
#define STATE_H

#include <vector>

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

class State
{
private:
    std::vector<sf::Texture> textures;
public:
    State();
    virtual ~State();

    virtual void update() = 0;
    virtual void render() = 0;
};
#endif