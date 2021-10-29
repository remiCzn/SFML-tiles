#include "HitboxComponent.hpp"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offset_X, float offset_Y, float width, float height)
    : sprite(sprite), offsetX(offset_X), offsetY(offset_Y)
{
    this->nextPosition.left = 0.f;
    this->nextPosition.top = 0.f;
    this->nextPosition.width = width;
    this->nextPosition.height = height;

    this->hitbox.setPosition(this->sprite.getPosition().x + offset_X, this->sprite.getPosition().y + offset_Y);
    this->hitbox.setSize(sf::Vector2f(width, height));
    this->hitbox.setFillColor(sf::Color::Transparent);
    this->hitbox.setOutlineThickness(-1.f);
    this->hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent()
{
}

bool HitboxComponent::intersects(const sf::FloatRect& rect)
{
    return this->hitbox.getGlobalBounds().intersects(rect);
}

const sf::Vector2f& HitboxComponent::getPosition() const {
    return this->hitbox.getPosition();
}

const sf::FloatRect HitboxComponent::getGlobalBounds() const {
    return this->hitbox.getGlobalBounds();
}

const sf::FloatRect& HitboxComponent::getNextPosition(const sf::Vector2f& velocity) {
    this->nextPosition.left = this->getPosition().x + velocity.x;
    this->nextPosition.top = this->getPosition().y + velocity.y;

    return this->nextPosition;
}

void HitboxComponent::setPosition(const float x, const float y) {
    this->hitbox.setPosition(x, y);
    this->sprite.setPosition(x + offsetX, y + offsetY);
}

void HitboxComponent::setPosition(const sf::Vector2f& position) {
    this->hitbox.setPosition(position);
    this->sprite.setPosition(position.x + offsetX, position.y + offsetY);
}

void HitboxComponent::update() {
    this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

void HitboxComponent::render(sf::RenderTarget& target) {
    target.draw(this->hitbox);
}