#include "SceneGameplay.h"

SceneGameplay::SceneGameplay(int w, int h)
{
	width = w;
	height = h;	
	map = new Map();
	map->generateMap();
	map->generateLights();
	conMap = new TCODConsole(48, 48);
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
		switch (key.vk){
		case TCODK_ESCAPE:
			activeScene = MAINMENU;
			break;
		}
		switch (key.c)
		{
		case 'w':
			if (map->map[map->player->x][map->player->y -1]->isWalkable && map->player->y > 0)
			{
				map->map[map->player->x][map->player->y]->isTransparent = true;
				map->player->y -= 1;
				map->map[map->player->x][map->player->y]->isTransparent = false;
				map->generateLights();
			}
			break;
		case 's':
			if (map->map[map->player->x][map->player->y + 1]->isWalkable && map->player->y < 50)
			{
				map->map[map->player->x][map->player->y]->isTransparent = true;
				map->player->y += 1;
				map->map[map->player->x][map->player->y]->isTransparent = false;
				map->generateLights();
			}
			break;
		case 'a':
			if (map->map[map->player->x - 1][map->player->y]->isWalkable && map->player->x > 0)
			{
				map->map[map->player->x][map->player->y]->isTransparent = true;
				map->player->x -= 1;
				map->map[map->player->x][map->player->y]->isTransparent = false;
				map->generateLights();
			}
			break;
		case 'd':
			if (map->map[map->player->x + 1][map->player->y]->isWalkable && map->player->x < 80)
			{
				map->map[map->player->x][map->player->y]->isTransparent = true;
				map->player->x += 1;
				map->map[map->player->x][map->player->y]->isTransparent = false;
				map->generateLights();
			}
			break;
		}
		for (auto& light : map->lights)
			if(map->player->x == light->x && map->player->y == light->y)
				map->map[map->player->x][map->player->y]->isTransparent = true;
	}
	else if (event == TCOD_EVENT_MOUSE_PRESS)
	{
		if (mouse.lbutton && mouse.cx < conMap->getWidth() && mouse.cy < conMap->getHeight())
		{
		}
	}
}

void SceneGameplay::render(TCODConsole *console)
{
	for (auto& light : map->lights)
		light->update();
	map->generateLights();
	console->setDefaultBackground(TCODColor::black);
	for (auto& row : map->map)
	{
		for (auto& tile : row)
		{
			conMap->putCharEx(tile->x, tile->y, tile->c, tile->foreColor, tile->tintColor * tile->luminosity);
		}
	}
	for (auto& obj : map->players)
	{	
		conMap->putCharEx(obj->x, obj->y, obj->c, obj->color, map->map[obj->x][obj->y]->backColor);
	}
	console->blit(conMap, 0, 0, conMap->getWidth(), conMap->getHeight(), console, 0, 0);
	console->print(1, height -2, "Mouse: %i, %i  FPS: %i", mouse.cx, mouse.cy, TCODSystem::getFps());
	if(mouse.cx > 0 && mouse.cx < 46 && mouse.cy > 0 && mouse.cy < 46)
		console->print(1, height - 4, "Tile Luminosity: %f", map->map[mouse.cx][mouse.cy]->luminosity);
}
