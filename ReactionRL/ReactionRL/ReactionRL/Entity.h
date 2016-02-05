#pragma once
#include <libtcod.hpp>

enum ENTITY_TYPE
{
	character, 
	light
};

class Entity
{
public:
	ENTITY_TYPE type;
	int x, y, ID, FoV;
	char c;
	TCODColor color;
	Entity(): x(0), y(0), c(' '), color(TCODColor::black), type(character), FoV(0){};

	void setEntityInfo(int x, int y, char c, TCODColor col, int id, int FoV, ENTITY_TYPE type)
	{
		this->x = x;
		this->y = y;
		this->c = c;
		this->color = col;
		this->ID = id;
		this->type = type;
		this->FoV = FoV;
	};
	virtual void update(TCOD_event_t event, TCOD_mouse_t mouse, TCOD_key_t key){};
	virtual void render(TCODConsole *console){};
};