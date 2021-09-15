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
    sf::Font* font;
    sf::Text pauseText;

    sf::RectangleShape background;
    sf::RectangleShape container;

    std::map<std::string, Button*> buttons;
public:
    PauseMenu(sf::RenderWindow& window, sf::Font* font);
    virtual ~PauseMenu();

    void update(const sf::Vector2f& mousePose);
    void render(sf::RenderTarget& target);

    std::map<std::string, Button*>& getButtons();
    const bool isButtonPressed(std::string key);
    void addButton(const std::string key, float y, const std::string text);
};

#endif