#pragma once
#include <libtcod.hpp>
#include <math.h>
class Player
{
public:
	int visibility, x, y, c, FoV, ID, flicker;
	TCODColor col;
	Player(int x, int y, char c, TCODColor color, int visibility, int FoV, int ID);
	~Player();
	void update();
	void render(TCODConsole *console);
};

