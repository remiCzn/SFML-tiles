#include "Stone.hpp"

_CustomTile* Stone::Clone(const int x, const int y, float gridSizeF) const {
	_CustomTile* stone = new Stone();
	stone->setPosition(x * gridSizeF, y * gridSizeF);
	stone->setCollision(true);
	return stone;
}

Stone::Stone() : _CustomTile("Stone", "src/images/Tiles/Stonex20.png") {};