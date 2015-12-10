#include "Player.h"


Player::Player(int x, int y,char c, TCODColor color, int vis, int FoV, int ID)
{
	this->x = x;
	this->y = y;
	this->c = c;
	this->FoV = FoV;
	this->flicker = 0;
	this->ID = ID;
	col = color;
	visibility = vis;
}

Player::~Player()
{
}

void Player::update()
{
	//TCODRandom *rand = TCODRandom::getInstance();
	//flicker = rand->getInt(0, 3);
}

void Player::render(TCODConsole *console)
{
	console->setCharForeground(x, y, col);
}