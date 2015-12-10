#pragma once
#include <libtcod.hpp>

class Tile
{
public:
	TCODColor backColor;
	TCODColor foreColor;
	TCODColor tintColor;
	int x, y;
	float luminosity;
	bool isWalkable, isTransparent, isVisible;
	char c;
	Tile(int x, int y, char c, TCODColor back, TCODColor front, bool isWalkable, bool isTransparent) :
		x(x), y(y), c(c), backColor(back),tintColor(back), foreColor(front), luminosity(0.0f), isWalkable(isWalkable), isTransparent(isTransparent), isVisible(true){};
};

