#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.hpp"
#include "../entities/Entity.hpp"
#include "./Chunk.hpp"

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

    std::map<std::pair<int, int>, Chunk *> chunkMap;
    unsigned chunkSizeInTiles;
    unsigned worldSizeInChunks;
    unsigned worldSizeInTiles;
    float worldSize;

    std::string saveFile;

public:
    // TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
    TileMap(float gridSize, unsigned worldSizeInChunks, unsigned chunkSize, std::string texture_file);
    virtual ~TileMap();

    const sf::Texture *getTileSheet() const;
    const int getLayerSize(const int x, const int y, const int layer) const;

    void update();
    void updateCollision(Entity *entity, const float &dt);

    void render(sf::RenderTarget &target, bool debugMode = true);
    void renderDeferred(sf::RenderTarget &target);

    void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect &texture_rect, bool collision, short type);
    void removeTile(const unsigned x, const unsigned y, const unsigned z);
    void saveToFile(const std::string file_name);
    void loadFromFile(const std::string file_name);
};

#endif