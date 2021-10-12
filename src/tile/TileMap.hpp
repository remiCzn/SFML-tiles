#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.hpp"

class TileMap
{
private:
    void clear();
    
    float gridSizeF;
    unsigned gridSizeU;
    sf::Vector2u maxSize;
    unsigned layers;
    std::vector<std::vector<std::vector<Tile *>>> map;
    std::string texture_file;
    sf::Texture tileSheet;

    std::string saveFile;
public:
    TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
    virtual ~TileMap();

    const sf::Texture* getTileSheet() const;

    void update();
    void render(sf::RenderTarget& target);

    void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect);
    void removeTile(const unsigned x, const unsigned y, const unsigned z);
    void saveToFile(const std::string file_name);
    void loadFromFile(const std::string file_name);

};

#endif