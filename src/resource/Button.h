#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

enum button_states{
    BTN_IDLE = 0,
    BTN_HOVER,
    BTN_ACTIVE
};

class Button
{
private:
    char buttonState;
    
    sf::RectangleShape shape;
    sf::Font *font;
    sf::Text text;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

public:
    Button(
        float x, 
        float y, 
        float width, 
        float height, 
        std::string text, 
        sf::Font *font,
        sf::Color idleColor,
        sf::Color hoverColor,
        sf::Color activeColor
    );
    ~Button();

    void update(const sf::Vector2f mousePose);
    void render(sf::RenderTarget *target);

    const bool isPressed() const;
};

#endif