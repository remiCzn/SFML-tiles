#ifndef TILE_REGISTRY_H
#define TILE_REGISTRY_H

#include "../headers/headers.hpp"
#include "./_CustomTile.hpp"

enum class TileType {
	STONE
};

class TileRegistry
{
private:
	TileRegistry();
	virtual ~TileRegistry();

	std::map<TileType, _CustomTile*> registry;

	static TileRegistry* _instance;

public:
	TileRegistry(TileRegistry& other) = delete;
	void operator=(const TileRegistry&) = delete;
	static TileRegistry* Instance();

	_CustomTile* CreateTile(TileType type);
};

TileRegistry* TileRegistry::_instance = nullptr;

#endif // !TILE_REGISTRY_H