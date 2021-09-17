#include "./gui.hpp"

gui::Button::Button(float x, float y, float width, float height,
               std::string text, sf::Font *font, unsigned character_size,
               sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
               sf::Color text_idleColor, sf::Color text_hoverColor, sf::Color text_activeColor,
               sf::Color outline_idleColor, sf::Color outline_hoverColor, sf::Color outline_ActiveColor,
               short unsigned id
               )
{
    this->id = id;
    
    this->buttonState = BTN_IDLE;
    this->lastState = BTN_IDLE;

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

    this->outlineActiveColor = outline_ActiveColor;
    this->outlineIdleColor = outline_idleColor;
    this->outlineHoverColor = outline_hoverColor;
}

gui::Button::Button(
        float x, float y, float width, float height,
        std::string text, sf::Font *font, unsigned character_size,
        short unsigned id
    )
{
    this->id = id;
    this->buttonState = BTN_IDLE;
    this->lastState = BTN_IDLE;

    // Default color buttons
    this->idleColor = sf::Color(70, 70, 70, 0);
    this->hoverColor = sf::Color(150, 150, 150, 0);
    this->activeColor = sf::Color(20, 20, 20, 0);

    this->textIdleColor = sf::Color(70, 70, 70, 200);
    this->textHoverColor = sf::Color(250, 250, 250, 250);
    this->textActiveColor = sf::Color(20, 20, 20, 50);

    this->outlineHoverColor = sf::Color(0,0,0,0);
    this->outlineActiveColor = sf::Color(0,0,0,0);
    this->outlineIdleColor = sf::Color(0,0,0,0);

    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setFillColor(this->idleColor);

    this->shape.setOutlineColor(this->outlineIdleColor);
    this->shape.setOutlineThickness(1.f);

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
    this->lastState = this->buttonState;
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
        this->shape.setOutlineColor(this->outlineIdleColor);
        break;
    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        this->text.setFillColor(this->textHoverColor);
        this->shape.setOutlineColor(this->outlineHoverColor);
        break;
    case BTN_ACTIVE:
        this->shape.setFillColor(this->activeColor);
        this->text.setFillColor(this->textActiveColor);
        this->shape.setOutlineColor(this->outlineActiveColor);
        break;
    default:
        this->shape.setFillColor(sf::Color::Red);
        this->text.setFillColor(sf::Color::Blue);
        this->shape.setOutlineColor(sf::Color::Green);
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

const bool gui::Button::isClicked() const {
    if(this->lastState == BTN_HOVER || this->lastState == BTN_IDLE)
    {
        return this->isPressed();
    }
    return false;
}

const std::string gui::Button::getText() const {
    return this->text.getString();
};

const short unsigned& gui::Button::getId() const {
    return this->id;
}

void gui::Button::setText(const std::string newText) {
    this->text.setString(newText);
}

void gui::Button::setId(const short unsigned id) {
    this->id = id;
}