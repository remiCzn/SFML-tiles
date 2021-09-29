#ifndef TILE_H
#define TILE_h

#include "../headers/headers.hpp"

class Tile
{
private:
    sf::RectangleShape shape;
public:
    Tile();
    Tile(float x, float y, float gridSizeF, sf::Texture& texture);
    virtual ~Tile();

    void update();
    void render(sf::RenderTarget& target);
};

#endif