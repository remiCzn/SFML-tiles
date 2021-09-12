#ifndef ENTITY_H
#define ENTITY_H

#include "../components/MovementComponent.hpp"

class Entity
{
private:
    void initVariables();
protected:
    sf::Sprite *sprite;
    sf::Texture *texture;

    // sf::RectangleShape shape;
    MovementComponent* movementComponent;

public:
    Entity(/* args */);
    virtual ~Entity();

    void createSprite(sf::Texture* texture);
    void createMovementComponent(const float maxSpeed);

    virtual void setPosition(const float x, const float y);
    virtual void move(const float &dt, const float x, const float y);

    virtual void update(const float &dt);
    virtual void render(sf::RenderTarget *target);
};

#endif