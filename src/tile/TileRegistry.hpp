#ifndef TILE_REGISTRY_H
#define TILE_REGISTRY_H

#include "../headers/headers.hpp"
#include "./Custom/Stone.hpp"
#include "./Custom/Dirt.hpp"
#include "./Custom/Tiletype.hpp"

class TileRegistry
{
private:
	TileRegistry();
	virtual ~TileRegistry();

	std::map<TileType, _CustomTile *> registry;
	std::map<TileType, sf::Texture *> texture_registry;

	static TileRegistry *_instance;

	template <class TileClass>
	void registerTile(TileType type);

public:
	TileRegistry(TileRegistry &other) = delete;
	void operator=(const TileRegistry &) = delete;
	static TileRegistry *Instance();

	_CustomTile *CreateTile(TileType type, const int x, const int y, const float gridSizeF);
};

#endif // !TILE_REGISTRY_H