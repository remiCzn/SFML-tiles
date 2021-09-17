#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.hpp"

class TileMap
{
private:
    float gridSizeF;
    unsigned gridSizeU;
    sf::Vector2u maxSize;
    unsigned layers;
    std::vector<std::vector<std::vector<Tile>>> map;
public:
    TileMap();
    virtual ~TileMap();

    void update();
    void render(sf::RenderTarget& target);
};

#endif