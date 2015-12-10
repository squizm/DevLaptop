#pragma once
#include <libtcod.hpp>
#include "Globals.h"

class  Scene
{
public:
	Scene(){};
	virtual void update(TCOD_event_t event, TCOD_mouse_t mouse, TCOD_key_t key){};
	virtual void render(TCODConsole *console){};
};
