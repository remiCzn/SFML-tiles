#ifndef TILE_REGISTRY_H
#define TILE_REGISTRY_H

#include "../headers/headers.hpp"
#include "./Custom/Stone.hpp"
#include "./Custom/Dirt.hpp"
#include "./Custom/Tiletype.hpp"

using namespace TileTypeNs;

class TileRegistry
{
private:
	TileRegistry();
	virtual ~TileRegistry();

	std::map<TileType, Tile *> registry;
	std::map<TileType, sf::Texture *> texture_registry;

	static TileRegistry *_instance;

	template <class TileClass>
	void registerTile(TileType type);

public:
	TileRegistry(TileRegistry &other) = delete;
	void operator=(const TileRegistry &) = delete;
	static TileRegistry *Instance();

	Tile *CreateTile(TileType type, const int x, const int y);
	const sf::Texture* getTexture(TileType type) const;
	const bool& isCollision(TileType type) const;
};

#endif // !TILE_REGISTRY_H