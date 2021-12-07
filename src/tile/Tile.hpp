#ifndef TILE_H
#define TILE_h

#include "../headers/headers.hpp"

enum TileTypes
{
    DEFAULT = 0,
    DAMAGING
};

class Tile
{
protected:
    sf::RectangleShape shape;
    bool collision;
    short type;

public:
    Tile();
    Tile(float x, float y, float gridSizeF, const sf::Texture &texture, const sf::IntRect &texture_rect,
         bool collision = false, short type = TileTypes::DEFAULT);
    virtual ~Tile();

    const bool &getCollision() const;
    const sf::Vector2f &getPosition() const;
    const sf::FloatRect getGlobalBounds() const;
    const Json::Value getAsJson() const;

    const bool intersects(const sf::FloatRect bounds) const;

    void update();
    void render(sf::RenderTarget &target);
};

#endif