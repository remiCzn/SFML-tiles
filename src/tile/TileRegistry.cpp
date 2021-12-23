#include "TileRegistry.hpp"

TileRegistry* TileRegistry::_instance = nullptr;

TileRegistry::TileRegistry() {
    registry[TileType::STONE] = new Stone();
    
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

_CustomTile* TileRegistry::CreateTile(TileType type,const int x, const int y, const float gridSizeF){
    return this->registry[type]->Clone(x, y, gridSizeF);
}


