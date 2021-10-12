#include "Tile.hpp"

Tile::Tile()
{
    this->collision = false;
    this->type = TileTypes::DEFAULT;
}

Tile::Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect, 
    bool collision, short type)
{
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->shape.setTexture(&texture);
    this->shape.setPosition(x, y);
    this->shape.setTextureRect(texture_rect);

    this->collision = collision;
    this->type = type;
}

void Tile::loadTile(Json::Value tile)
{
    //TODO: Load tile from json value (from savefile)
}

Tile::~Tile()
{
}

const Json::Value Tile::getAsJson() const {
    Json::Value result;
    result["trX"] = this->shape.getTextureRect().left;
    result["trY"] = this->shape.getTextureRect().top;
    result["collision"] = this->collision;
    result["type"] = this->type;
    return result;
}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target)
{
    target.draw(this->shape);
}