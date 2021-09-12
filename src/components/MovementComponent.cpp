#include "MovementComponent.hpp"

MovementComponent::MovementComponent(float maxVelocity)
{
    this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::update(const float& dt)
{

}

void MovementComponent::move(const float dir_x, const float dir_y, const float dt)
{
    this->velocity.x = this->maxVelocity * dir_x;
    this->velocity.y = this->maxVelocity * dir_y;
}

const sf::Vector2f & MovementComponent::getVelocity() const{
    return this->velocity;
}