#pragma once
#include <libtcod.hpp>

class Tile
{
public:

	enum TILE_TYPE {
		Destructible = 0x01,
		Transparent = 0x02,
		Blocking = 0x03,
		Invisible = 0x04,
		Walkable = 0x05,
		Opaque = 0x06
	};

	TCODColor backColor;
	TCODColor foreColor;
	TCODColor tintColor;
	int x, y, flags;
	float luminosity;
	char c;
	Tile(int x, int y, char c, TCODColor back, TCODColor front, int flags) :
		x(x), y(y), c(c), backColor(back), tintColor(back), foreColor(front), luminosity(0.0f), flags(flags) {};
};

