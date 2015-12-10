#pragma once
#include <libtcod.hpp>

class Entity
{
public:
	int x, y, ID;
	char c;
	int FoV;
	TCODColor col;
	Entity(){};
	Entity(int x, int y, char c, TCODColor col):x(x),y(y), c(c), col(col), ID(-1){};
	virtual void update(TCOD_event_t event, TCOD_mouse_t mouse, TCOD_key_t key){};
	virtual void render(TCODConsole *console){};
};