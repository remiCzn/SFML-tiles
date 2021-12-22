#include "TileRegistry.hpp"

TileRegistry::TileRegistry() {
    registry[TileType::STONE] = new _CustomTile("Stone");
}

TileRegistry::~TileRegistry()
{
    delete registry[TileType::STONE];
    registry[TileType::STONE] = NULL;
}

TileRegistry* TileRegistry::Instance()
{
    if (_instance == nullptr) {
        _instance = new TileRegistry();
    }
    return _instance;
}

_CustomTile* TileRegistry::CreateTile(TileType type){}


