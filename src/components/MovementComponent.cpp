#include "MovementComponent.hpp"

MovementComponent::MovementComponent(sf::Sprite* sprite,
    float maxVelocity,
    float acceleration,
    float decceleration)
    : sprite(sprite), 
      maxVelocity(maxVelocity), 
      acceleration(acceleration), 
      deceleration(decceleration),
      state(IDLE_DOWN)
{
    
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::update(const float& dt)
{
    if(this->velocity.y > 0.f)
    {
        if(this->velocity.y > this->maxVelocity)
            this->velocity.y = this->maxVelocity;
        
        this->velocity.y -= deceleration;
        if(abs(this->velocity.y) > abs(this->velocity.x))
        {
            this->state = MOVING_DOWN;
        }

        if(this->velocity.y < 0.f)
        {
            this->velocity.y = 0.f;
            this->state = IDLE_DOWN;
        } 
    }

    if(this->velocity.y < 0.f)
    {
        if(this->velocity.y < - this->maxVelocity)
            this->velocity.y = -maxVelocity;
        
        this->velocity.y += deceleration;
        if(abs(this->velocity.y) > abs(this->velocity.x))
        {
            this->state = MOVING_UP;
        }
    
        if(this->velocity.y > 0.f)
        {
            this->velocity.y = 0.f;
            this->state = IDLE_UP;
        }
    }

    if(this->velocity.x > 0.f)
    {
        if(this->velocity.x > this->maxVelocity)
            this->velocity.x = this->maxVelocity;
        
        this->velocity.x -= deceleration;
        if(abs(this->velocity.x) > abs(this->velocity.y))
        {
            this->state = MOVING_RIGHT;
        }

        if(this->velocity.x < 0.f)
        {
            this->velocity.x = 0.f;
            this->state = IDLE_RIGHT;
        }
    }

    if(this->velocity.x < 0.f)
    {
        if(this->velocity.x < - this->maxVelocity)
            this->velocity.x = -maxVelocity;
        
        this->velocity.x += deceleration;
        if(abs(this->velocity.x) > abs(this->velocity.y))
        {
            this->state = MOVING_LEFT;
        }
        
        if(this->velocity.x > 0.f)
        {
            this->velocity.x = 0.f;
            this->state = IDLE_LEFT;
        }
    }

    this->sprite->move(this->velocity * dt);
}

void MovementComponent::move(const float dir_x, const float dir_y, const float dt)
{
    this->velocity.x += this->acceleration * dir_x;
    this->velocity.y += this->acceleration * dir_y;
}

const sf::Vector2f & MovementComponent::getVelocity() const{
    return this->velocity;
}

const short MovementComponent::getState() const {
    return this->state;
}

const float& MovementComponent::getMaxVelocity() const
{
    return this->maxVelocity;
}