#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ctime>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

class Game
{
private:
    //Variables
    sf::RenderWindow *window;
    sf::Event sfEvent;
    //Init
    void initWindow();
public:
    Game();
    ~Game();

    void updateSFMLEvent();
    void update();
    void render();
    void run();
};

#endif