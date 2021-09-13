#include "Entity.hpp"

Entity::Entity(/* args */)
{
    this->initVariables();
}

void Entity::initVariables()
{
    this->sprite = new sf::Sprite();
    this->movementComponent = NULL;
}

Entity::~Entity()
{
    delete this->sprite;
}

void Entity::setPosition(const float x, const float y)
{
    this->sprite->setPosition(x, y);
}

void Entity::move(const float &dt, const float dir_x, const float dir_y)
{
    if (this->movementComponent)
    {
        this->movementComponent->move(dir_x, dir_y, dt);
    }
}

void Entity::setTexture(sf::Texture* texture)
{
    this->sprite->setTexture(*texture);
}

void Entity::createSprite(sf::Texture *texture)
{
    this->sprite->setTexture(*texture);
}

void Entity::createMovementComponent(const float maxSpeed, const float acceleration, const float decceleration)
{
    this->movementComponent = new MovementComponent(this->sprite, maxSpeed, acceleration, decceleration);
}

void Entity::update(const float &dt)
{
    if(this->movementComponent)
        this->movementComponent->update(dt);
}

void Entity::render(sf::RenderTarget *target)
{
    target->draw(*this->sprite);
}