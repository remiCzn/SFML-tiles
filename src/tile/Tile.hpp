#ifndef TILE_H
#define TILE_H

#include "../headers/headers.hpp"
#include "./Custom/Tiletype.hpp"

using namespace TileTypeNs;

class Tile
{
protected:
    sf::Sprite shape;
    float gridSizeF;
    bool collision;

    std::string name;
    std::string tilesheet_name;
    TileType type;

public:
    Tile();
    Tile(float x, float y, float gridSizeF, const sf::Texture &texture, const sf::IntRect &texture_rect,
         bool collision = false);
    Tile(std::string name, TileType type, std::string tilesheet_name, bool collision, float gridSizeF);
    virtual ~Tile();

    void setTexture(const sf::Texture &texture);

    const bool &getCollision() const;
    void setCollision(const bool &isCollision);
    const sf::Vector2f &getPosition() const;
    void setPosition(const float x, const float y);
    const sf::FloatRect getGlobalBounds() const;
    const Json::Value getAsJson() const;
    const bool intersects(const sf::FloatRect bounds) const;

    void update();
    void render(sf::RenderTarget &target, sf::Shader *shader = NULL, sf::Vector2f playerPosition = sf::Vector2f());

    virtual Tile *Clone(const int x, const int y) const = 0;
    void setTexture(const sf::Texture *texture, const sf::IntRect &texture_rect);
    const std::string &getTextureFile() const;
};

#endif