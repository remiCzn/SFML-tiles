#include "Tile.hpp"

Tile::Tile()
{
    this->collision = false;
    this->type = TileTypes::DEFAULT;
}

Tile::Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect, 
    bool coll, short type)
{
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->shape.setTexture(&texture);
    this->shape.setPosition(x, y);
    this->shape.setTextureRect(texture_rect);

    this->collision = coll;
    this->type = type;
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

const bool& Tile::getCollision() const {
    return this->collision;
}

const sf::Vector2f& Tile::getPosition() const {
    return this->shape.getPosition();
}

const sf::FloatRect Tile::getGlobalBounds() const {
    return this->shape.getGlobalBounds();
}

const bool Tile::intersects(const sf::FloatRect bounds) const {
    return this->shape.getGlobalBounds().intersects(bounds);
}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target)
{
    target.draw(this->shape);
}