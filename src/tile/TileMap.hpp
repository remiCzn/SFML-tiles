#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.hpp"

class TileMap
{
private:
    unsigned gridSizeU;
    sf::Vector2u maxSize;
    unsigned layers;
    std::vector<std::vector<std::vector<Tile>>> map;
public:
    TileMap();
    virtual ~TileMap();
};

#endif