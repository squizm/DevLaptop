#include "Character.h"

Character::Character(int x, int y, char img, int FoV) : x(x), y(y), FoV(FoV), img(img)
{
	isPlayer = false;
	destX = x;
	destY = y;
}

Character::~Character()
{
	delete path;
}

void Character::update(TCOD_event_t event, TCOD_mouse_t mouse, TCOD_key_t key, uint32 deltaTime)
{

}

void Character::render(TCODConsole *console)
{
	console->printEx(x, y, TCOD_BKGND_DEFAULT, TCOD_alignment_t::TCOD_LEFT, &img);
}