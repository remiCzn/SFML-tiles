#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

enum button_states
{
    BTN_IDLE = 0,
    BTN_HOVER,
    BTN_ACTIVE
};
namespace gui {

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

        sf::Color textIdleColor;
        sf::Color textHoverColor;
        sf::Color textActiveColor;

    public:
        Button(
            float x, float y, float width, float height,
            std::string text, sf::Font *font, unsigned character_size,
            sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
            sf::Color text_idleColor, sf::Color text_hoverColor, sf::Color text_activeColor
        );
        Button(
            float x, float y, float width, float height,
            std::string text, sf::Font *font, unsigned character_size
        );
        ~Button();

        void update(const sf::Vector2f& mousePose);
        void render(sf::RenderTarget *target);

        const bool isPressed() const;
    };

    class DropDownList
    {
    private:
        float keytime;
        float keytimeMax;

        sf::Font* font;
        gui::Button* activeElement;
        std::vector<gui::Button*> list;
        bool showList;
    public:
        DropDownList(
            float x, float y, float width, float height,
            sf::Font* font, std::string list[],
            unsigned nrOfElements, unsigned default_index = 0
        );
        ~DropDownList();

        const bool getKeyTime();
        void updateKeytime(const float& dt);
        void update(const sf::Vector2f& mousePos, const float& dt);
        void render(sf::RenderTarget* target);
    };    
}


#endif