#include "Player.hpp"

void Player::initComponents() {
    this->createMovementComponent(300.f, 15.f, 7.f);
}

void Player::initVariables() {
    
}

Player::Player(float x, float y, sf::Texture* texture_sheet)
{
    this->initVariables();
    this->initComponents();

    //this->createSprite(texture);
    //Change according to the sprite scale
    this->sprite->setScale(sf::Vector2f(2.f, 2.f));
    //
    this->setPosition(x,y);

    this->createMovementComponent(300.f, 15.f, 5.f);
    this->createAnimationComponent(*texture_sheet);
    this->animationComponent->addAnimation("IDLE_DOWN", 10.f, 0, 0, 4, 64, 64);
}

Player::~Player()
{
}

void Player::update(const float& dt)
{
    this->movementComponent->update(dt);
    //this->animationComponent->play("IDLE_DOWN", dt);
}