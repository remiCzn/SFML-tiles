#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include "../../headers/headers.hpp"

enum ProgressBarType
{
    LARGE,
    MEDIUM,
    THICK
};

enum ProgressBarMode
{
    PERCENT,
    ABSOLUT,
    FRAC
};

class progressBar
{
private:
    float maxWidth;
    sf::RectangleShape innerBar;
    sf::RectangleShape backBar;
    sf::Text DispValue;

    ProgressBarMode mode;

public:
    progressBar(float x, float y, float width, ProgressBarType heightType, sf::Font &font, sf::Color backColor, sf::Color innerColor);
    ~progressBar();

    void setProgressBarMode(ProgressBarMode mode);

    void update(int value, int maxValue);
    void render(sf::RenderTarget &target);
};
#endif