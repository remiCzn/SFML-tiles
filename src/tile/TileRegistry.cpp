#include "TileRegistry.hpp"

TileRegistry *TileRegistry::_instance = nullptr;

TileRegistry::TileRegistry()
{
    this->registerTile<Stone>(TileType::STONE);
    this->registerTile<Dirt>(TileType::DIRT);

}

TileRegistry::~TileRegistry()
{
    delete registry[TileType::STONE];
    delete registry[TileType::DIRT];
    registry[TileType::STONE] = NULL;
    registry[TileType::DIRT] = NULL;
}

TileRegistry *TileRegistry::Instance()
{
    if (_instance == nullptr)
    {
        _instance = new TileRegistry();
    }
    return _instance;
}

Tile *TileRegistry::CreateTile(TileType type, const int x, const int y)
{
    Tile *tile = this->registry[type]->Clone(x, y);
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

const sf::Texture* TileRegistry::getTexture(TileType type) const {
    return this->texture_registry.at(type);
}

const bool& TileRegistry::isCollision(TileType type) const {
    return this->registry.at(type)->getCollision();
}
