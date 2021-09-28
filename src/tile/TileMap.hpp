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
    std::vector<std::vector<std::vector<Tile *>>> map;
public:
    TileMap(float gridSize, unsigned width, unsigned height);
    virtual ~TileMap();

    void update();
    void render(sf::RenderTarget& target);

    void addTile(const unsigned x, const unsigned y, const unsigned z);
    void removeTile();


};

#endif