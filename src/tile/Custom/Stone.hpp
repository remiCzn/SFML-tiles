#ifndef STONE_TILE_H
#define STONE_TILE_H

#include "../Tile.hpp"

class Stone :
    public Tile
{
private:
public:
    Stone();
    virtual ~Stone() {};

    Tile* Clone(const int x, const int y) const override;
};

#endif

