#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>

#include "./resource/Button.hpp"

#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"

class PauseMenu
{
private:
    sf::RectangleShape background;
    sf::RectangleShape container;

    std::map<std::string, Button*> buttons;
public:
    PauseMenu(sf::RenderWindow& window);
    virtual ~PauseMenu();

    void update();
    void render(sf::RenderTarget& target);
};

#endif