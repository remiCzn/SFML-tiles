#include "HitboxComponent.hpp"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offset_X, float offset_Y, float width, float height)
    : sprite(sprite), offsetX(offset_X), offsetY(offset_Y)
{
    this->hitbox.setPosition(this->sprite.getPosition().x + offset_X, this->sprite.getPosition().y + offset_Y);
    this->hitbox.setSize(sf::Vector2f(width, height));
    this->hitbox.setFillColor(sf::Color::Transparent);
    this->hitbox.setOutlineThickness(1.f);
    this->hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent()
{
}

bool HitboxComponent::checkIntersect(const sf::FloatRect& rect)
{
    return this->hitbox.getGlobalBounds().intersects(rect);
}

void HitboxComponent::update() {
    this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

void HitboxComponent::render(sf::RenderTarget& target) {
    target.draw(this->hitbox);
}