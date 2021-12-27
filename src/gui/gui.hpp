#ifndef GUI_H
#define GUI_H

#include "../headers/headers.hpp"
#include "../tile/TileRegistry.hpp"

enum button_states
{
    BTN_IDLE = 0,
    BTN_HOVER,
    BTN_ACTIVE
};
namespace gui
{

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
            short unsigned id);
        Button(
            float x, float y, float width, float height,
            std::string text, sf::Font *font, unsigned character_size,
            short unsigned id = 0);
        ~Button();

        void update(const sf::Vector2i &mousePoseWindow);
        void render(sf::RenderTarget *target);

        const std::string getText() const;
        const short unsigned &getId() const;

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

        sf::Font *font;
        gui::Button *activeElement;
        std::vector<gui::Button *> list;
        bool showList;

    public:
        DropDownList(
            float x, float y, float width, float height,
            sf::Font *font, std::string list[],
            unsigned nrOfElements, unsigned default_index = 0);
        ~DropDownList();

        const bool getKeyTime();
        void updateKeytime(const float &dt);
        void update(const sf::Vector2i &mousePoseWindow, const float &dt);
        void render(sf::RenderTarget *target);

        const unsigned short &getActiveElementId() const;
        void setActiveElement(const short &id);
    };

    class TextureSelector
    {
    private:
        float keytime;
        const float keyTimeMax;
        float gridSize;
        bool active;
        bool hidden;
        gui::Button *hide_btn;
        sf::RectangleShape bounds;
        std::vector<sf::Sprite> sheets;
        sf::RectangleShape selector;
        sf::Vector2u mousePosGrid;

        TileType type;


        
        float scale;

    public:
        TextureSelector(float x, float y, float width, float height,
                        float gridSize, sf::Font &font, std::string text);
        ~TextureSelector();

        const bool &getActive() const;
        const TileType& getType() const;
        const bool getKeytime();
        void updateKeytime(const float &dt);
        void update(const sf::Vector2i &mousePosWindow, const float &dt);
        void render(sf::RenderTarget &target);
    };

    class CheckBox
    {
    private:
        sf::RectangleShape box;
        sf::CircleShape cross;
        bool value;

        short lastState;

        void initCross(float x, float y, float width);

    public:
        CheckBox(float x, float y, float width, bool defaultValue = false);
        virtual ~CheckBox();

        const bool getValue() const;
        void setValue(const bool value);

        void update(const sf::Vector2i &mousePoseWindow);
        void render(sf::RenderTarget *target);
    };
}

#endif