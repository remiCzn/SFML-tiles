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
    std::vector<std::vector<std::vector<std::vector<Tile *>>>> map;
    std::stack<Tile *> deferredRenderStack;
    std::string texture_file;
    sf::RectangleShape collisionBox;

    std::map<std::pair<int, int>, Chunk *> chunkMap;
    int chunkSizeInTiles;
    int worldSizeInChunks;
    int worldSizeInTiles;
    float worldSize;

    std::string saveFile;

public:
    // TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
    TileMap(float gridSize, int worldSizeInChunks, unsigned chunkSize, std::string texture_file);
    virtual ~TileMap();

    const sf::Texture *getTileSheet() const;

    void update();
    void updateCollision(Entity *entity, const float &dt);

    void renderDeferred(sf::RenderTarget &target);
    void render(
        sf::RenderTarget &target,
        bool debugMode = true,
        const sf::Vector2i &mousePosition = sf::Vector2i(),
        const sf::Vector2i &chunkCenter = sf::Vector2i());

    void addTile(const int x, const int y, TileType type);
    void removeTile(const int x, const int y, const unsigned z);
    void saveToFile(const std::string file_name);
    void loadFromFile(const std::string file_name);

    const float& getWorldSize() const;
};

#endif