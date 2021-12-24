#include "TileRegistry.hpp"

TileRegistry *TileRegistry::_instance = nullptr;

TileRegistry::TileRegistry()
{
    this->registerTile<Stone>(TileType::STONE);
}

TileRegistry::~TileRegistry()
{
    delete registry[TileType::STONE];
    registry[TileType::STONE] = NULL;
}

TileRegistry *TileRegistry::Instance()
{
    if (_instance == nullptr)
    {
        _instance = new TileRegistry();
    }
    return _instance;
}

_CustomTile *TileRegistry::CreateTile(TileType type, const int x, const int y, const float gridSizeF)
{
    _CustomTile *tile = this->registry[type]->Clone(x, y, gridSizeF);
    tile->setTexture(this->texture_registry[type], sf::IntRect(0, 0, 20, 20));
    return tile;
}

template <class TileClass>
void TileRegistry::registerTile(TileType type)
{
    registry[type] = new TileClass();
    this->texture_registry[type] = new sf::Texture();
    if (!this->texture_registry[type]->loadFromFile(registry[type]->getTextureFile()))
    {
        std::cout << "ERROR:TILEREGISTRY::COULD NOT LOAD FONT FOR " << (int)type << std::endl;
    }
}
