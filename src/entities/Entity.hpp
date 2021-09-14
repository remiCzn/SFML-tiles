#ifndef ENTITY_H
#define ENTITY_H

#include "../components/MovementComponent.hpp"
#include "../components/AnimationComponent.hpp"
#include "../components/HitboxComponent.hpp"

class Entity
{
private:
    void initVariables();
protected:
    sf::Sprite *sprite;

    // sf::RectangleShape shape;
    MovementComponent* movementComponent;
    AnimationComponent* animationComponent;
    HitboxComponent* hitboxComponent;

public:
    Entity();
    virtual ~Entity();

    void createSprite(sf::Texture* texture);
    void setTexture(sf::Texture* texture);
    void createHitboxComponent(float offsetX, float offsetY, float width, float height);
    void createMovementComponent(const float maxSpeed, const float acceleration, const float deceleration);
    void createAnimationComponent(sf::Texture& textureSheet);

    virtual void setPosition(const float x, const float y);
    virtual void move(const float &dt, const float x, const float y);

    virtual void update(const float &dt);
    virtual void render(sf::RenderTarget *target);
};

#endif