#pragma once
#include "Scene.h"
#include "Character.h"
#include "Map.h"

#define MAP_WIDTH	72
#define MAP_HEIGHT	72
#define MAX_CHARACTERS	10

class SceneCampaign :
	public Scene
{
private:
	int width, height;
	TCOD_mouse_t mouse;
	TCOD_event_t evt;
	TCOD_key_t key;
	Map* map;
	Character* player;
	Character* characters[MAX_CHARACTERS];
	TCODConsole* menuConsole;
public:
	SceneCampaign(int width, int height);
	~SceneCampaign();
	void update(TCOD_event_t event, TCOD_mouse_t mouse, TCOD_key_t key, uint32 delta);
	void render(TCODConsole *console);
};