#pragma once
#include <libtcod.hpp>

class Character
{
public:
	int x, y;
	int FoV;
	char img;
	bool isPlayer;
	Character(int x, int y, char img, int FoV);
	void update(TCOD_event_t event, TCOD_mouse_t mouse, TCOD_key_t key, uint32 deltaTime);
	void render(TCODConsole *console);
};