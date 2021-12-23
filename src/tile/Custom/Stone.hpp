#ifndef STONE_TILE_H
#define STONE_TILE_H

#include "../_CustomTile.hpp"

class Stone :
    public _CustomTile
{
private:
    sf::Texture texture;
public:
    Stone();
    virtual ~Stone() {};

    _CustomTile* Clone(const int x, const int y, float gridSizeF) const override;
};

#endif

