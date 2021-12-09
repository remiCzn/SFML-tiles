#include "./progressBar.hpp"

progressBar::progressBar(float x, float y, float width, ProgressBarType heightType, sf::Font &font, sf::Color backColor, sf::Color innerColor)
{
    this->maxWidth = width;

    float height;
    switch (heightType)
    {
    case ProgressBarType::THICK:
        height = 10.f;
        break;
    case ProgressBarType::MEDIUM:
        height = 25.f;
        break;
    case ProgressBarType::LARGE:
    default:
        height = 50.f;
        break;
    }

    this->backBar.setSize(sf::Vector2f(width, height));
    this->backBar.setFillColor(backColor);
    this->backBar.setOutlineColor(sf::Color::White);
    this->backBar.setOutlineThickness(1.f);
    this->backBar.setPosition(x, y);

    this->innerBar.setSize(sf::Vector2f(width, height));
    this->innerBar.setFillColor(innerColor);
    this->innerBar.setOutlineColor(sf::Color::White);
    this->innerBar.setOutlineThickness(1.f);
    this->innerBar.setPosition(this->backBar.getPosition());

    this->DispValue.setFont(font);
    this->DispValue.setCharacterSize(18);
    this->DispValue.setString("100%");
    this->DispValue.setPosition(x + width / 2.f - this->DispValue.getGlobalBounds().width / 2.f, y + height / 2.f - this->DispValue.getGlobalBounds().height / 2.f);
}

progressBar::~progressBar()
{
    delete this->font;
}

void progressBar::update(int value, int maxValue)
{
    float percent = static_cast<float>(value) / static_cast<float>(maxValue);
    this->DispValue.setString(std::to_string(static_cast<int>(percent * 100)).append("%"));
    this->innerBar.setSize(
        sf::Vector2f(
            static_cast<float>(std::floor(this->maxWidth * percent)),
            this->innerBar.getSize().y));
}

void progressBar::render(sf::RenderTarget &target)
{
    target.draw(this->backBar);
    target.draw(this->innerBar);
    target.draw(this->DispValue);
}