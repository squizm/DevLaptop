#pragma once
#include <libtcod.hpp>
#include "Scene.h"
#include "SceneMainMenu.h"
#include "SceneGameplay.h"

class GameEngine
{
public:
	TCOD_key_t key;
	TCOD_mouse_t mouse;
	TCODConsole *console;
	GAMESTATE state;

	GameEngine();
	~GameEngine();

	void update();
	void render();
private:
	Scene *sceneList[2];
};

