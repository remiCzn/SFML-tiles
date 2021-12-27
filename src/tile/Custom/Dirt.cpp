#include "Dirt.hpp"

Tile* Dirt::Clone(const int x, const int y) const {
	Tile* tile = new Dirt(*this);
	tile->setPosition(x * this->gridSizeF, y * this->gridSizeF);
	return tile;
}

Dirt::Dirt() : Tile("Dirt", TileType::DIRT, "src/images/Tiles/Dirtx20.png", true, 20.f) {};