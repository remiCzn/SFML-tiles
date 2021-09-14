#include "Player.hpp"

void Player::initVariables() {
    
}

Player::Player(float x, float y, sf::Texture* texture_sheet)
{
    this->initVariables();

    //this->createSprite(texture);
    //Change according to the sprite scale
    this->sprite->setScale(sf::Vector2f(2.f, 2.f));
    //
    this->setPosition(x,y);
    // this->sprite->setOrigin(sf::Vector2f(this->sprite->getGlobalBounds().width / 2.f, this->sprite->getGlobalBounds().height / 2.f));

    this->createHitboxComponent(48.f, 32.f, 32.f, 64.f);
    this->createMovementComponent(300.f, 15.f, 7.f);
    this->createAnimationComponent(*texture_sheet);

    float idle_anim_timer = 8.f;
    this->animationComponent->addAnimation("IDLE_DOWN", idle_anim_timer, 4, 0, 0, 64, 64);
    this->animationComponent->addAnimation("IDLE_UP", idle_anim_timer, 4, 0, 1, 64, 64);
    this->animationComponent->addAnimation("IDLE_LEFT", idle_anim_timer, 4, 0, 2, 64, 64);
    this->animationComponent->addAnimation("IDLE_RIGHT", idle_anim_timer, 4, 0, 3, 64, 64);

    float walk_anim_timer = 5.f;
    this->animationComponent->addAnimation("WALK_DOWN", walk_anim_timer , 5, 0, 4, 64, 64);
    this->animationComponent->addAnimation("WALK_UP", walk_anim_timer, 5, 0, 5, 64, 64);
    this->animationComponent->addAnimation("WALK_LEFT", walk_anim_timer, 5, 0, 6, 64, 64);
    this->animationComponent->addAnimation("WALK_RIGHT", walk_anim_timer, 5, 0, 7, 64, 64);
}

Player::~Player()
{
}

void Player::update(const float& dt)
{
    this->movementComponent->update(dt);
    this->playAnimations(dt);
    this->hitboxComponent->update();
}

void Player::playAnimations(const float& dt)
{
    switch (this->movementComponent->getState())
    {
    case IDLE_DOWN:
        this->animationComponent->play("IDLE_DOWN",dt);
        break;
    case IDLE_UP:
        this->animationComponent->play("IDLE_UP",dt);
        break;
    case IDLE_LEFT:
        this->animationComponent->play("IDLE_LEFT",dt);
        break;
    case IDLE_RIGHT:
        this->animationComponent->play("IDLE_RIGHT",dt);
        break;
    case MOVING_DOWN:
        this->animationComponent->play("WALK_DOWN",dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
        break;
    case MOVING_LEFT:
        this->animationComponent->play("WALK_LEFT",dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
        break;
    case MOVING_RIGHT:
        this->animationComponent->play("WALK_RIGHT",dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
        break;
    case MOVING_UP:
        this->animationComponent->play("WALK_UP",dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
        break;
    
    default:
        this->animationComponent->play("IDLE_DOWN",dt);
        break;
    }
}