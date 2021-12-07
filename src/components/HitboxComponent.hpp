#ifndef HITBOX_COMP_H
#define HITBOX_COMP_H

#include "../headers/headers.hpp"

class HitboxComponent
{
private:
    sf::Sprite &sprite;
    sf::RectangleShape hitbox;
    sf::FloatRect nextPosition;
    float offsetX;
    float offsetY;

public:
    HitboxComponent(sf::Sprite &sprite, float offset_X, float offset_Y, float width, float height);
    virtual ~HitboxComponent();

    const sf::Vector2f &getPosition() const;
    const sf::FloatRect getGlobalBounds() const;
    const sf::FloatRect &getNextPosition(const sf::Vector2f &velocity);

    void setPosition(const sf::Vector2f &position);
    void setPosition(const float x, const float y);

    bool intersects(const sf::FloatRect &frect);

    void update();
    void render(sf::RenderTarget &target, bool debugMode);
};

#endif