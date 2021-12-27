#ifndef DIRT_TILE_H
#define DIRT_TILE_H

#include "../Tile.hpp"

class Dirt :
    public Tile
{
private:
public:
    Dirt();
    virtual ~Dirt() {};

    Tile* Clone(const int x, const int y) const override;

};

#endif // !DIRT_TILE_HPP

