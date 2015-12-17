#include "SceneGameplay.h"

SceneGameplay::SceneGameplay(int w, int h)
{
	width = w;
	height = h;	
	map = new Map();
	map->generateMap();
	map->generateLights();
	conMap = new TCODConsole(120, 80);
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
			if (map->map[map->player->x][map->player->y - 1]->isWalkable && map->player->y > 0)
			{
				map->map[map->player->x][map->player->y]->isTransparent = true;
				map->player->y -= 1;
				map->map[map->player->x][map->player->y]->isTransparent = false;
				map->generateLights();
			}
			break;
		case 's':
			if (map->map[map->player->x][map->player->y + 1]->isWalkable && map->player->y < map->MAP_HEIGHT)
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
			if (map->map[map->player->x + 1][map->player->y]->isWalkable && map->player->x < map->MAP_WIDTH)
			{
				map->map[map->player->x][map->player->y]->isTransparent = true;
				map->player->x += 1;
				map->map[map->player->x][map->player->y]->isTransparent = false;
				map->generateLights();
			}
			break;
		}
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
	for (auto& row : map->map)
	{
		for (auto& tile : row)
		{
			conMap->putCharEx(tile->x, tile->y, tile->c, tile->foreColor, tile->backColor);
		}
	}
	for (auto& obj : map->game_objects)
	{
		switch (obj->type)
		{
		case ENTITY_TYPE::character:
			conMap->putCharEx(obj->x, obj->y, obj->c, obj->color, TCODColor::red);
			break;
		case ENTITY_TYPE::light :
			conMap->putCharEx(obj->x, obj->y, obj->c, obj->color, TCODColor::white);
			break;
		}
		
	}
	console->blit(conMap, 0, 0, conMap->getWidth(), conMap->getHeight(), console, 0, 0);
	
	map->mapLights->blitRect(console, 0, 0, -1, -1, TCOD_BKGND_SET);

	console->print(1, height -2, "Mouse: %i, %i  FPS: %i", mouse.cx, mouse.cy, TCODSystem::getFps());
}
