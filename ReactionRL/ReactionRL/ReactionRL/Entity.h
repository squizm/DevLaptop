#pragma once
#include <libtcod.hpp>

class Entity
{
public:
	int x, y, ID, FoV;
	char c;
	TCODColor color;
	Entity(): x(0), y(0), c(' '), color(TCODColor::black), FoV(0){};

	void setEntityInfo(int x, int y, char c, TCODColor col, int id, int FoV)
	{
		this->x = x;
		this->y = y;
		this->c = c;
		this->color = col;
		this->ID = id;
		this->FoV = FoV;
	};
	virtual void update(TCOD_event_t event, TCOD_mouse_t mouse, TCOD_key_t key, uint32 deltaTime){};
	virtual void render(TCODConsole *console){};
};