#include "Tile.hpp"

Tile::Tile()
{
    this->collision = false;
    this->type = TileTypes::DEFAULT;
}

Tile::Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect, bool collision, short type)
{
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->shape.setTexture(&texture);
    this->shape.setPosition(x, y);
    this->shape.setTextureRect(texture_rect);

    this->collision = collision;
    this->type = type;
}

Tile::~Tile()
{
}

const std::string Tile::getAsString() const {
    std::stringstream ss;
    ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision << " " << this->type;
    return ss.str();
}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target)
{
    target.draw(this->shape);
}