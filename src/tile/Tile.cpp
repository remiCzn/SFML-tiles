#include "Tile.hpp"

Tile::Tile()
{}

Tile::Tile(float x, float y, float gridSizeF, sf::Texture& texture)
{
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->shape.setTexture(&texture);
    this->shape.setPosition(x, y);
}

Tile::~Tile()
{
}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target)
{
    target.draw(this->shape);
}