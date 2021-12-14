#include "./progressBar.hpp"

progressBar::progressBar(float x, float y, float width, ProgressBarType heightType, sf::Font &font, sf::Color backColor, sf::Color innerColor)
{
    this->maxWidth = width;

    float height;
    switch (heightType)
    {
    case ProgressBarType::THICK:
        height = 10.f;
        this->DispValue.setPosition(x, y + height);
        break;
    case ProgressBarType::MEDIUM:
        height = 25.f;
        this->DispValue.setPosition(x + width / 3.f, y);
        break;
    case ProgressBarType::LARGE:
    default:
        height = 50.f;
        this->DispValue.setPosition(x + width / 3.f, y + height / 3.f);
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
}

progressBar::~progressBar()
{
}

void progressBar::setProgressBarMode(ProgressBarMode mode)
{
    this->mode = mode;
}

void progressBar::update(int value, int maxValue)
{
    float percent = static_cast<float>(value) / static_cast<float>(maxValue);

    this->innerBar.setSize(
        sf::Vector2f(
            static_cast<float>(std::floor(this->maxWidth * percent)),
            this->innerBar.getSize().y));

    switch (this->mode)
    {
    case ProgressBarMode::ABSOLUTE:
        this->DispValue.setString(std::to_string(value));
        break;
    case ProgressBarMode::FRAC:
        this->DispValue.setString(std::to_string(value) + "/" + std::to_string(maxValue));
        break;
    case ProgressBarMode::PERCENT:
    default:
        this->DispValue.setString(std::to_string(static_cast<int>(percent * 100)).append("%"));
        break;
    }
}

void progressBar::render(sf::RenderTarget &target)
{
    target.draw(this->backBar);
    target.draw(this->innerBar);
    target.draw(this->DispValue);
}