#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include "../../headers/headers.hpp"

enum ProgressBarType
{
    LARGE,
    MEDIUM,
    THICK
};

class progressBar
{
private:
    sf::Font *font;

    float maxWidth;
    sf::RectangleShape innerBar;
    sf::RectangleShape backBar;
    sf::Text DispValue;

public:
    progressBar(float x, float y, float width, ProgressBarType heightType, sf::Font &font, sf::Color backColor, sf::Color innerColor);
    ~progressBar();

    void update(int value, int maxValue);
    void render(sf::RenderTarget &target);
};
#endif