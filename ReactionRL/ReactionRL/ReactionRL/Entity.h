#pragma once
#include <libtcod.hpp>

class Entity
{
public:
	int x, y, ID;
	char c;
	TCODColor color;
	Entity(): x(0), y(0), c(' '), color(TCODColor::black){};
	void setEntityInfo(int x, int y, char c, TCODColor col, int id)
	{
		this->x = x;
		this->y = y;
		this->c = c;
		this->color = col;
		this->ID = id;
	};
	virtual void update(TCOD_event_t event, TCOD_mouse_t mouse, TCOD_key_t key){};
	virtual void render(TCODConsole *console){};
};