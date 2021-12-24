#include "Stone.hpp"

Tile* Stone::Clone(const int x, const int y) const {
	Tile* stone = new Stone(*this);
	stone->setPosition(x * this->gridSizeF, y * this->gridSizeF);
	return stone;
}

Stone::Stone() 
	: Tile(
		"Stone", 
		TileType::STONE, 
		"src/images/Tiles/Stonex20.png", 
		true, 
		20.f
	) {};