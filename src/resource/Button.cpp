#include "gui.hpp"

gui::Button::Button(float x, float y, float width, float height,
               std::string text, sf::Font *font, unsigned character_size,
               sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
               sf::Color text_idleColor, sf::Color text_hoverColor, sf::Color text_activeColor
               )
{
    this->buttonState = BTN_IDLE;

    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setFillColor(idleColor);

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(text_idleColor);
    this->text.setCharacterSize(character_size);

    this->text.setPosition(
        this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f);

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->textIdleColor = text_idleColor;
    this->textHoverColor = text_hoverColor;
    this->textActiveColor = text_activeColor;
}

gui::Button::Button(
        float x, float y, float width, float height,
        std::string text, sf::Font *font, unsigned character_size
    )
{
    this->buttonState = BTN_IDLE;

    // Default color buttons
    this->idleColor = sf::Color(70, 70, 70, 0);
    this->hoverColor = sf::Color(150, 150, 150, 0);
    this->activeColor = sf::Color(20, 20, 20, 0);

    this->textIdleColor = sf::Color(70, 70, 70, 200);
    this->textHoverColor = sf::Color(250, 250, 250, 250);
    this->textActiveColor = sf::Color(20, 20, 20, 50);

    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setFillColor(this->idleColor);

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(this->textIdleColor);
    this->text.setCharacterSize(character_size);

    this->text.setPosition(
        this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f);
}

gui::Button::~Button()
{
}

void gui::Button::update(const sf::Vector2f& mousePose)
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
        this->text.setFillColor(this->textIdleColor);
        break;
    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        this->text.setFillColor(this->textHoverColor);
        break;
    case BTN_ACTIVE:
        this->shape.setFillColor(this->activeColor);
        this->text.setFillColor(this->textActiveColor);
        break;
    default:
        this->shape.setFillColor(sf::Color::Red);
        this->text.setFillColor(sf::Color::Blue);
        break;
    }
}

void gui::Button::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
    target->draw(this->text);
}

const bool gui::Button::isPressed() const
{
    if (this->buttonState == BTN_ACTIVE)
        return true;
    return false;
}