#ifndef __GLOBALS__
#define __GLOBALS__

extern int activeScene;
extern bool running;

enum ACTIVE_SCREEN
{
	MAINMENU,
	CAMPAIGN,
	TGEN
};

enum GAMESTATE
{
	MENU,
	GAMEPLAY,
	PLAYERMOVE,
	ENEMYMOVE,
	PLAYERACTION, 
	ENEMYACTION
};

#endif