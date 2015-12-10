#include "Player.h"


Player::Player(int x, int y,char c, TCODColor color, int vis, int FoV, int ID)
{
	setEntityInfo(x, y, c, color, ID);
	this->FoV = FoV;
	this->flicker = 0;
	this->visibility = vis;
}

Player::~Player()
{
}

void Player::update()
{
	//do AI things?
}

void Player::render(TCODConsole *console)
{
	console->setCharForeground(x, y, color);
}