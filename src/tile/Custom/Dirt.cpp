#include "Dirt.hpp"

_CustomTile* Dirt::Clone(const int x, const int y, float gridSizeF) const {
	_CustomTile* tile = new Dirt();
	tile->setPosition(x * gridSizeF, y * gridSizeF);
	tile->setCollision(true);
	return tile;
}

Dirt::Dirt() : _CustomTile("Dirt", "src/images/Tiles/Dirtx20.png", TileType::DIRT) {};