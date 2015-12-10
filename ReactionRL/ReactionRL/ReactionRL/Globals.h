#ifndef __GLOBALS__
#define __GLOBALS__

extern int activeScene;
extern bool running;

enum GAMESTATE
{
	MAINMENU = 0,
	GAMEPLAY = 1,
	PLAYERMOVE,
	ENEMYMOVE,
	PLAYERACTION, 
	ENEMYACTION
};

#endif