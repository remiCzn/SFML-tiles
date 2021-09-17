#ifndef TILE_H
#define TILE_h

#include "../resource/headers.hpp"

class Tile
{
private:
    sf::RectangleShape shape;
public:
    Tile();
    Tile(float x, float y, float gridSizeF);
    virtual ~Tile();

    void update();
    void render(sf::RenderTarget& target);
};

#endif