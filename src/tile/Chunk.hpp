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
    std::vector<std::vector<std::vector<std::vector<Tile *>>>> chunk;
    std::stack<Tile *> deferredRenderStack;
    sf::Texture &tileSheet;
    sf::RectangleShape collisionBox;

    void clear();

public:
    Chunk(float gridSize, sf::Texture &tilesheet, sf::RectangleShape &collisionBox);
    virtual ~Chunk();

    void update();

    void addTile(const unsigned x, const unsigned y, const unsigned offsetX, const unsigned offsetY, const unsigned z, const sf::IntRect &texture_rect, bool collision, short type);
    void removeTile(const unsigned x, const unsigned y, const unsigned z);

    void render(sf::RenderTarget &target, bool debugMode, sf::Vector2i offSet);
    void renderDeferred(sf::RenderTarget &target, sf::Vector2i offSet);

    Json::Value getAsJson();
};

#endif