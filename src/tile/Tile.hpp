#ifndef TILE_H
#define TILE_H

#include "../headers/headers.hpp"

class Tile
{
protected:
    sf::RectangleShape shape;
    bool collision;

public:
    Tile();
    Tile(float x, float y, float gridSizeF, const sf::Texture &texture, const sf::IntRect &texture_rect,
         bool collision = false);
    virtual ~Tile();

    void setTexture(const sf::Texture& texture);

    const bool &getCollision() const;
    void setCollision(const bool& isCollision);
    const sf::Vector2f &getPosition() const;
    void setPosition(const float x, const float y);
    const sf::FloatRect getGlobalBounds() const;
    const Json::Value getAsJson() const;

    const bool intersects(const sf::FloatRect bounds) const;

    void update();
    void render(sf::RenderTarget &target);
};

#endif