#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "./gui.hpp"
#include "../headers/headers.hpp"

class PauseMenu
{
private:
    sf::Font *font;
    sf::Text pauseText;

    sf::RectangleShape background;
    sf::RectangleShape container;

    std::map<std::string, gui::Button *> buttons;

public:
    PauseMenu(sf::RenderWindow &window, sf::Font *font);
    virtual ~PauseMenu();

    void update(const sf::Vector2i &mousePoseWindow);
    void render(sf::RenderTarget &target);

    std::map<std::string, gui::Button *> &getButtons();
    const bool isButtonPressed(std::string key);
    void addButton(const std::string key, float y, const std::string text);
};

#endif