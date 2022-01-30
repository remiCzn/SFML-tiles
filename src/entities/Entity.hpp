#ifndef ENTITY_H
#define ENTITY_H

#include "../components/MovementComponent.hpp"
#include "../components/AnimationComponent.hpp"
#include "../components/HitboxComponent.hpp"
#include "../components/AttributeComponent.hpp"

class Entity
{
private:
    void initVariables();

protected:
    sf::Sprite *sprite;

    // sf::RectangleShape shape;
    MovementComponent *movementComponent;
    AnimationComponent *animationComponent;
    HitboxComponent *hitboxComponent;
    AttributeComponent *attributeComponent;

public:
    Entity();
    virtual ~Entity();

    void createSprite(sf::Texture *texture);
    void setTexture(sf::Texture *texture);
    void createHitboxComponent(float offsetX, float offsetY, float width, float height);
    void createMovementComponent(const float maxSpeed, const float acceleration, const float deceleration);
    void createAnimationComponent();
    void createAttributeComponent(const unsigned level);

    virtual const sf::Vector2f &getPosition() const;
    virtual const sf::FloatRect getGlobalBounds() const;
    virtual void setPosition(const float x, const float y);
    virtual const sf::FloatRect &getNextPosition(const float &dt) const;
    virtual const sf::Vector2i getGridPosition(const int gridSizeU) const;

    virtual void move(const float &dt, const float x, const float y);
    virtual void stopVelocity();
    virtual void stopVelocityX();
    virtual void stopVelocityY();

    virtual void update(const float &dt) = 0;
    virtual void render(sf::RenderTarget &target, bool debugMode) = 0;
};

#endif