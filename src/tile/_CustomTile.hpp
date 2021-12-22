#ifndef CUSTOM_TILE_H
#define CUSTOM_TILE_H

#include "./Tile.hpp"

/*
	Prototype class, allow to create Tile types
*/
class _CustomTile : public Tile
{
protected:
	std::string name;

public:
	_CustomTile() {};
	_CustomTile(std::string name) : name(name) {};
	virtual ~_CustomTile() {};
	virtual _CustomTile* Clone() const = 0;

};

#endif

