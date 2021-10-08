#include "gui.hpp"

gui::CheckBox::CheckBox(float x, float y, float width, bool defaultValue) 
{
    this->lastState = BTN_IDLE;
    this->box.setPosition(sf::Vector2f(
        x, y
    ));
    this->box.setSize(sf::Vector2f(
        width, width
    ));
    this->box.setOutlineThickness(1.f);
    this->box.setOutlineColor(sf::Color::Black);
    this->box.setFillColor(sf::Color::White);

    this->initCross(x, y, width);
    this->value = defaultValue;
}

void gui::CheckBox::initCross(float x, float y, float width) {
    cross.setPosition(sf::Vector2f(x+2, y+2));
    cross.setRadius((width - 4.f) / 2.f);
    cross.setFillColor(sf::Color::Black);
}

gui::CheckBox::~CheckBox() {
}

const bool gui::CheckBox::getValue() const {
    return this->value;
}

void gui::CheckBox::setValue(const bool value) {
    this->value = value;
}

void gui::CheckBox::update(const sf::Vector2f& mousePose) {
    if(this->box.getGlobalBounds().contains(mousePose) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(this->lastState == BTN_IDLE) {
            this->value = !this->value;
            this->lastState = BTN_ACTIVE;
        }
        
    } else {
        this->lastState = BTN_IDLE;
    }
}

void gui::CheckBox::render(sf::RenderTarget* target) {
    target->draw(this->box);
    if(value) {
        target->draw(cross);
    }
}