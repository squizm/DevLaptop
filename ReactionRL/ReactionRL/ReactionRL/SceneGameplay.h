#pragma once
#include "Scene.h"
#include "Map.h"

class SceneGameplay : public Scene
{
public:
	int width, height;
	Map* map;
	SceneGameplay(int w, int h);
	~SceneGameplay();
	TCOD_event_t event;
	TCOD_mouse_t mouse;
	TCOD_key_t key;
	TCODImage* testIMG;


	void update(TCOD_event_t event, TCOD_mouse_t mouse, TCOD_key_t key);
	void render(TCODConsole *console);
};

