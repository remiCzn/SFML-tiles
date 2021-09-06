#include "Entity.h"

Entity::Entity(/* args */)
{
    this->initVariables();
    
}

void Entity::initVariables()
{
    this->moveSpeed = 100.f;
    this->sprite = NULL;
    this->texture = NULL;
}

Entity::~Entity()
{
    delete this->sprite;
    delete this->texture;
}

void Entity::move(const float& dt, const float dir_x, const float dir_y)
{
    if(this->sprite)
    {
     this->sprite->move(dir_x * this->moveSpeed * dt, dir_y * this->moveSpeed * dt);
    }
}

void Entity::createSprite(sf::Texture* texture)
{
    this->texture = texture;
    this->sprite->setTexture(*this->texture);
}

void Entity::update(const float & dt)
{
    
}

void Entity::render(sf::RenderTarget* target)
{   
    if(this->sprite)
    {
        target->draw(*this->sprite);
    }
}