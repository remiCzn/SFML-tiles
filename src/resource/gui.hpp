#ifndef GUI_H
#define GUI_H

#include "../headers/headers.hpp"

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
        short unsigned id;

        char buttonState;
        short lastState;

        sf::RectangleShape shape;
        sf::Font *font;
        sf::Text text;

        sf::Color idleColor;
        sf::Color hoverColor;
        sf::Color activeColor;

        sf::Color textIdleColor;
        sf::Color textHoverColor;
        sf::Color textActiveColor;

        sf::Color outlineIdleColor;
        sf::Color outlineHoverColor;
        sf::Color outlineActiveColor;

    public:
        Button(
            float x, float y, float width, float height,
            std::string text, sf::Font *font, unsigned character_size,
            sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
            sf::Color text_idleColor, sf::Color text_hoverColor, sf::Color text_activeColor,
               sf::Color outline_idleColor, sf::Color outline_hoverColor, sf::Color outline_ActiveColor,
               short unsigned id
        );
        Button(
            float x, float y, float width, float height,
            std::string text, sf::Font *font, unsigned character_size,
            short unsigned id = 0
        );
        ~Button();

        void update(const sf::Vector2f& mousePose);
        void render(sf::RenderTarget *target);

        const std::string getText() const;
        const short unsigned& getId() const;

        void setText(const std::string newText);
        void setId(const short unsigned id); 

        const bool isPressed() const;
        const bool isClicked() const;
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

        const unsigned short& getActiveElementId() const;
    };    
}


#endif