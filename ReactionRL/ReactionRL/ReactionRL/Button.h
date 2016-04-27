#pragma once
#include "Entity.h"

class Button : public Entity
{
public:
	const char* text;
	void (*onClick)();
	int width, height;
	TCODColor backColor;
	TCODColor foreColor;
	TCODColor hoverColor;
	bool isHover;
	Button(int x,int y, const char* text, void (*function)(), TCODColor backColor = TCODColor::darkestGrey, TCODColor foreColor = TCODColor::white, TCODColor hoverColor = TCODColor::red );
	void update(TCOD_event_t event, TCOD_mouse_t mouse, TCOD_key_t key, uint32 deltaTime);
	void render(TCODConsole *console);
};

