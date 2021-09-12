#include "Entity.hpp"

Entity::Entity(/* args */)
{
    this->initVariables();
}

void Entity::initVariables()
{
    this->sprite = NULL;
    this->texture = NULL;

    this->movementComponent = NULL;
}

Entity::~Entity()
{
    delete this->sprite;
    delete this->texture;
}

void Entity::setPosition(const float x, const float y)
{
    if (this->sprite)
    {
        this->sprite->setPosition(x, y);
    }
}

void Entity::move(const float &dt, const float dir_x, const float dir_y)
{
    if (this->sprite && this->movementComponent)
    {
        this->movementComponent->move(dir_x, dir_y, dt);
        this->sprite->move(this->movementComponent->getVelocity() * dt);
    }
}

void Entity::createSprite(sf::Texture *texture)
{
    this->texture = texture;
    this->sprite = new sf::Sprite(*this->texture);
    this->sprite->setTexture(*this->texture);
}

void Entity::createMovementComponent(const float maxSpeed)
{
    this->movementComponent = new MovementComponent(maxSpeed);
}

void Entity::update(const float &dt)
{
}

void Entity::render(sf::RenderTarget *target)
{
    if (this->sprite)
    {
        target->draw(*this->sprite);
    }
}