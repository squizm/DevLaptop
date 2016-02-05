#include "SceneGameplay.h"

void generateSomething(TCODImage* img)
{
	TCODRandom* rng = TCODRandom::getInstance();
	int x, y;
	img->getSize(&x, &y);
	for (int row = 0; row < x; row++)
	{
		for (int column = 0; column < y; column++)
		{
			img->putPixel(row, column, TCODColor(rng->getInt(1, 254), rng->getInt(1, 254), rng->getInt(1, 254) * row/x));
		}
	}
}

SceneGameplay::SceneGameplay(int w, int h)
{
	width = w;
	height = h;	
	map = new Map();
	map->generateMap();
	testIMG = new TCODImage(w, h);
}

SceneGameplay::~SceneGameplay()
{
	delete map;
}

void SceneGameplay::update(TCOD_event_t event, TCOD_mouse_t mouse, TCOD_key_t key)
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
			//LMB Clicked inside window
		}
	}
	generateSomething(testIMG);
}

void SceneGameplay::render(TCODConsole *console)
{
	TCODConsole::root->setDefaultBackground(TCODColor::black);
	TCODConsole::root->clear();
	testIMG->blit2x(TCODConsole::root, 0, 0);
	/*
	for (auto& tile : map->map)
	{
		TCODConsole::root->putCharEx(tile->x, tile->y, tile->c, tile->foreColor, tile->backColor);
	}

	for (auto& obj : map->objects)
	{
		TCODConsole::root->putCharEx(obj->x, obj->y, obj->c, obj->color, TCODColor::red);
	}
	*/
	console->print(1, height -2, "Mouse: %i, %i  FPS: %i", mouse.cx, mouse.cy, TCODSystem::getFps());
	console->flush();
}
