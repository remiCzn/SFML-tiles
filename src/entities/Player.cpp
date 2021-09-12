#include "Player.hpp"

void Player::initComponents() {
    this->createMovementComponent(100.f);
}

void Player::initVariables() {
    
}

Player::Player(float x, float y, sf::Texture* texture)
{
    this->initVariables();
    this->initComponents();

    this->createSprite(texture);
    //Change according to the sprite scale
    this->sprite->setScale(sf::Vector2f(2.f, 2.f));
    //
    this->setPosition(x,y);
}

Player::~Player()
{
}