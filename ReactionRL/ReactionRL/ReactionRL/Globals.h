#ifndef __GLOBALS__
#define __GLOBALS__

extern int activeScene;
extern bool running;

enum GAMESTATE
{
	MAINMENU,
	GAMEPLAY,
	PLAYERMOVE,
	ENEMYMOVE,
	PLAYERACTION, 
	ENEMYACTION
};

#endif