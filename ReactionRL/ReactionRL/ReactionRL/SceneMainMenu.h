#pragma once
#include <libtcod.hpp>
#include "Scene.h"
#include "Button.h"

class SceneMainMenu : public Scene
{
public:
	int width, height, numButtons;
	TCOD_mouse_t mouse;
	TCOD_event_t evt;
	TCOD_key_t key;
	Button *buttons[4];

	SceneMainMenu(int w, int h);
	~SceneMainMenu();
	void update(TCOD_event_t event, TCOD_mouse_t mouse, TCOD_key_t key, uint32 delta);
	void render(TCODConsole *console);
};

