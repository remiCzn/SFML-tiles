#ifndef TILETYPE_H
#define TILETYPE_H

namespace TileTypeNs {
	enum class TileType
	{
		STONE,
		DIRT,
		NONE
	};

	static const TileType All[] = { TileType::STONE, TileType::DIRT };
}


#endif // !TILETYPE_H

