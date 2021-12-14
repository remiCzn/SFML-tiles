#ifndef CHUNK_H
#define CHUNK_H

#include "../headers/headers.hpp"
#include "Tile.hpp"

class Chunk
{
private:
    float gridSizeF;
    unsigned gridSizeU;
    unsigned chunkWidthGrid;
    float chunkWidthF;

    unsigned layers;
    std::vector<std::vector<std::vector<Tile *>>> chunk;
    std::stack<Tile *> deferredRenderStack;
    sf::Texture &tileSheet;
    sf::RectangleShape collisionBox;

    void clear();

public:
    Chunk(float gridSize, sf::Texture &tilesheet, sf::RectangleShape &collisionBox);
    virtual ~Chunk();

    void update();

    void addTile(const unsigned x, const unsigned y, const unsigned offsetX, const unsigned offsetY, const sf::IntRect &texture_rect, bool collision, short type);
    void removeTile(const unsigned x, const unsigned y);
    const std::vector<Tile *> getTileStack(const unsigned x, const unsigned y);

    void render(sf::RenderTarget &target, bool debugMode);
    void renderDeferred(sf::RenderTarget &target);

    Json::Value getAsJson();
    void loadFromJson(Json::Value chunk, const int offsetX, const int offsetY);
};

#endif