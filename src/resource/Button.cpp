#include "Button.h"

Button::Button(float x, float y, float width, float height,
               std::string text, sf::Font *font,
               sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
    this->buttonState = 0;

    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setPosition(sf::Vector2f(x, y));
    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(12);

    this->text.setPosition(
        this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f);

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{
}

void Button::update(const sf::Vector2f mousePose)
{
    this->buttonState = BTN_IDLE;
    if (this->shape.getGlobalBounds().contains(mousePose))
    // == if hover
    {
        this->buttonState = BTN_HOVER;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->buttonState = BTN_ACTIVE;
        }
    }

    switch (this->buttonState)
    {
    case BTN_IDLE:
        this->shape.setFillColor(this->idleColor);
        break;
    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        break;
    case BTN_ACTIVE:
        this->shape.setFillColor(this->activeColor);
        break;
    default:
        this->shape.setFillColor(sf::Color::Red);
        break;
    }
}

void Button::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
    target->draw(this->text);
}

const bool Button::isPressed() const
{
    if (this->buttonState == BTN_ACTIVE)
        return true;
    return false;
}