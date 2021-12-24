#ifndef DIRT_TILE_H
#define DIRT_TILE_H

#include "../_CustomTile.hpp"

class Dirt :
    public _CustomTile
{
private:
public:
    Dirt();
    virtual ~Dirt() {};

    _CustomTile* Clone(const int x, const int y, float gridSizeF) const override;

};

#endif // !DIRT_TILE_HPP

