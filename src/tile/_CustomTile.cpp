#include "_CustomTile.hpp"

_CustomTile::_CustomTile() : name(""), type(TileType::NONE), Tile(0.f, 0.f, 20.f, sf::Texture(), sf::IntRect(0, 0, 20, 20))
{
}

_CustomTile::_CustomTile(std::string name, std::string tilesheetFile, TileType tiletype) : name(name), tilesheet_name(tilesheetFile), type(tiletype), Tile(0.f, 0.f, 20.f, sf::Texture(), sf::IntRect(0, 0, 20, 20))
{
}

void _CustomTile::setTexture(const sf::Texture *texture, const sf::IntRect &texture_rect)
{
	this->shape.setTexture(texture);
	this->shape.setTextureRect(texture_rect);
}

const std::string& _CustomTile::getTextureFile() const
{
	return this->tilesheet_name;
}

const Json::Value _CustomTile::getAsJson() const{
    Json::Value result;
	if (this->type != TileType::NONE) {
		result["id"] = static_cast<int>(this->type);
	} 
    return result;
};
