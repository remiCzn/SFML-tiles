#include "gui.hpp"

gui::CheckBox::CheckBox(float x, float y, float width, bool defaultValue) 
{
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
    sf::Texture texture;
    if(!texture.loadFromFile("images/UI/check-mark.png"))
    {
        std::cout << "ERROR::CHECKBOX::COULD NOT LOAD CHECKBOX SPRITE" << std::endl;
        return;
    }
    this->cross.setTexture(texture);
    this->cross.setPosition(sf::Vector2f(x, y));
    this->cross.setScale(sf::Vector2f(width / texture.getSize().x, width / texture.getSize().y));
}

gui::CheckBox::~CheckBox() {
}

const bool gui::CheckBox::getValue() const {
    return this->value;
}

void gui::CheckBox::update(const sf::Vector2f& mousePose) {

}

void gui::CheckBox::render(sf::RenderTarget* target) {
    target->draw(this->box);
    if(value) {
        target->draw(this->cross);
    }
}