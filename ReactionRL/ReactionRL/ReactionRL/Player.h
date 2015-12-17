#pragma once
#include <libtcod.hpp>
#include "Entity.h"

class Player : public Entity
{
public:
	int visibility, flicker;
	Player();
	Player(int x, int y, char c, TCODColor color, int visibility, int FoV, int ID);
	~Player();
	void update();
	void render(TCODConsole *console);
};

