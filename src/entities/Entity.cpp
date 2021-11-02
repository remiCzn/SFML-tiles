#include "Entity.hpp"
#include "../headers/headers.hpp"

Entity::Entity(/* args */)
{
    this->initVariables();
}

void Entity::initVariables()
{
    this->sprite = new sf::Sprite();
    this->movementComponent = NULL;
    this->hitboxComponent = NULL;
    this->animationComponent = NULL;
}

Entity::~Entity()
{
    delete this->sprite;
    delete this->hitboxComponent;
    delete this->animationComponent;
    delete this->movementComponent;
}

void Entity::setPosition(const float x, const float y)
{
    if(this->hitboxComponent)
        this->hitboxComponent->setPosition(x,y);
    else
        this->sprite->setPosition(x, y);
}

const sf::Vector2f& Entity::getPosition() const {
    if(this->hitboxComponent)
        return this->hitboxComponent->getPosition();

    return this->sprite->getPosition();
}

const sf::FloatRect Entity::getGlobalBounds() const
{
    if(this->hitboxComponent)
        return this->hitboxComponent->getGlobalBounds();

    return this->sprite->getGlobalBounds();
}

const sf::FloatRect& Entity::getNextPosition(const float& dt) const {
    if(this->hitboxComponent && this->movementComponent) {
        return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);
    }
    std::cout << "Calculate next position need hitbox & movement component";
    throw;
}

const sf::Vector2u Entity::getGridPosition(const unsigned gridSizeU) const {
    if(this->hitboxComponent)
        return sf::Vector2u(
            static_cast<unsigned>(this->hitboxComponent->getPosition().x) / gridSizeU,
            static_cast<unsigned>(this->hitboxComponent->getPosition().y) / gridSizeU
        );
    
    return sf::Vector2u(
        static_cast<unsigned>(this->sprite->getPosition().x) / gridSizeU,
        static_cast<unsigned>(this->sprite->getPosition().y) / gridSizeU
    );
}

void Entity::move(const float &dt, const float dir_x, const float dir_y)
{
    this->movementComponent->move(dir_x, dir_y, dt);
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

void Entity::createAnimationComponent(sf::Texture& textureSheet)
{
    this->animationComponent = new AnimationComponent(this->sprite, textureSheet);
}

void Entity::createHitboxComponent(
    float offsetX, float offsetY,
    float width, float height
)
{
    this->hitboxComponent = new HitboxComponent(*this->sprite, offsetX, offsetY, width, height);
}

void Entity::update(const float &dt)
{
    if(this->movementComponent)
        this->movementComponent->update(dt);
}

void Entity::stopVelocity(){
    if(this->movementComponent)
        this->movementComponent->stopVelocity();
}

void Entity::stopVelocityX(){
    if(this->movementComponent)
        this->movementComponent->stopVelocityX();
}

void Entity::stopVelocityY(){
    if(this->movementComponent)
        this->movementComponent->stopVelocityY();
}

void Entity::render(sf::RenderTarget &target, bool debugMode)
{

}