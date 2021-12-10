#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.hpp"
#include "../entities/Entity.hpp"

class TileMap
{
private:
    void clear();

    float gridSizeF;
    unsigned gridSizeU;
    sf::Vector2u maxSizeWorldGrid;
    sf::Vector2f maxSizeWorldF;
    unsigned layers;
    std::vector<std::vector<std::vector<std::vector<Tile *>>>> map;
    std::stack<Tile *> deferredRenderStack;
    std::string texture_file;
    sf::Texture tileSheet;
    sf::RectangleShape collisionBox;

    std::string saveFile;

public:
    TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
    virtual ~TileMap();

    const sf::Texture *getTileSheet() const;
    const int getLayerSize(const int x, const int y, const int layer) const;

    void update();
    void updateCollision(Entity *entity, const float &dt);

    void render(sf::RenderTarget &target, sf::Shader *shader = NULL, const sf::Vector2f playerPosition = sf::Vector2f(), bool debugMode = true);
    void renderDeferred(sf::RenderTarget &target, sf::Shader *shader = NULL, const sf::Vector2f playerPosition = sf::Vector2f());

    void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect &texture_rect, bool collision, short type);
    void removeTile(const unsigned x, const unsigned y, const unsigned z);
    void saveToFile(const std::string file_name);
    void loadFromFile(const std::string file_name);
};

#endif