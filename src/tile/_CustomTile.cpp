#include "_CustomTile.hpp"

_CustomTile::_CustomTile() : name(""), Tile(0.f, 0.f, 20.f, sf::Texture(), sf::IntRect(0, 0, 20.f, 20.f))
{
}

_CustomTile::_CustomTile(std::string name, std::string tilesheetFile): name(name), Tile(0.f, 0.f, 20.f, sf::Texture(), sf::IntRect(0, 0, 20.f, 20.f)) {
	this->tilesheet_name = tilesheetFile;
}

void _CustomTile::setTexture(const sf::Texture* texture, const sf::IntRect& texture_rect)
{
	this->shape.setTexture(texture);
	this->shape.setTextureRect(texture_rect);
}
