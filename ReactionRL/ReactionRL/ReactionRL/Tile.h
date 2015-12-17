#pragma once
#include <libtcod.hpp>

class Tile
{
public:

	enum TILE_TYPE {
		solid,
		water,
		lava
	};

	TCODColor backColor;
	TCODColor foreColor;
	TCODColor tintColor;
	int x, y, type;
	float luminosity;
	bool isWalkable, isTransparent, isVisible;
	char c;
	Tile(int x, int y, char c, TCODColor back, TCODColor front, int type, bool isWalkable, bool isTransparent) :
		x(x), y(y), c(c), backColor(back), tintColor(back), foreColor(front), luminosity(0.0f), isWalkable(isWalkable), isTransparent(isTransparent), isVisible(true), type(type) {};
};

