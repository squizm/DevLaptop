#include "SceneGameplay.h"

SceneGameplay::SceneGameplay(int w, int h)
{
	width = w;
	height = h;	
	map = new Map(80, 80);
	map->generateWorldMap();
}

SceneGameplay::~SceneGameplay()
{
	delete map;
}

void SceneGameplay::update(TCOD_event_t event, TCOD_mouse_t mouse, TCOD_key_t key, uint32 delta)
{
	this->event = event;
	this->mouse = mouse;
	this->key = key;
	if (event == TCOD_EVENT_KEY_RELEASE)
	{
		switch (key.vk) {
		case TCODK_ESCAPE:
			activeScene = MAINMENU;
			break;
		}
		switch (key.c)
		{
		case 'w':
			break;
		case 's':
			break;
		case 'a':
			break;
		case 'd':
			break;
		}
	}
	else if (event == TCOD_EVENT_MOUSE_PRESS)
	{
		if (mouse.lbutton && mouse.cx <TCODConsole::root->getWidth() && mouse.cy < TCODConsole::root->getWidth())
		{
			// render new heightmap
			map->generateWorldMap();
		}
	}
}

void SceneGameplay::render(TCODConsole *console)
{
	console->setDefaultBackground(TCODColor::black);

	console->blit(map->mapImage, 0, 0, 0, 0, TCODConsole::root, 1, 0);
	
	console->print(1, height -2, "Mouse: %i, %i  FPS: %i", mouse.cx, mouse.cy, TCODSystem::getFps());
}