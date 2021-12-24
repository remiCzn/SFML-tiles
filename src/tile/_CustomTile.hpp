#ifndef CUSTOM_TILE_H
#define CUSTOM_TILE_H

#include "./Tile.hpp"
#include "./Custom/Tiletype.hpp"

/*
	Prototype class, allow to create Tile types
*/
class _CustomTile : public Tile
{
protected:
	std::string name;
	std::string tilesheet_name;
	TileType type;

public:
	_CustomTile();
	_CustomTile(std::string name, std::string tilesheetFile, TileType tiletype);
	virtual ~_CustomTile(){};
	virtual _CustomTile *Clone(const int x, const int y, float gridSizeF) const = 0;

	void setTexture(const sf::Texture *texture, const sf::IntRect &texture_rect);
	const std::string& getTextureFile() const;

	const Json::Value getAsJson() const;
};

#endif