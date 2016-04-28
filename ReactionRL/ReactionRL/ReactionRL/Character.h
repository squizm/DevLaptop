#pragma once
#include <libtcod.hpp>

class Character
{
public:
	int x, y;
	int destX, destY;
	int FoV;
	char img;
	bool isPlayer;
	TCODPath* path;
	Character(int x, int y, char img, int FoV);
	~Character();
	void update(TCOD_event_t event, TCOD_mouse_t mouse, TCOD_key_t key, uint32 deltaTime);
	void render(TCODConsole *console);
};