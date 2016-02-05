#include "Player.h"


Player::Player(int x, int y,char c, TCODColor color, int vis, int FoV, int ID)
{
	setEntityInfo(x, y, c, color, ID, FoV, ENTITY_TYPE::character);
	this->visibility = vis;
}

Player::Player()
{
	setEntityInfo(-1, -1, ' ', TCODColor::purple, -1, 0, ENTITY_TYPE::character);
	this->visibility = 0;
}

Player::~Player()
{
}

void Player::update()
{
	//TODO: Finite state machine
}

void Player::render(TCODConsole *console)
{
	console->setCharForeground(x, y, color);
}