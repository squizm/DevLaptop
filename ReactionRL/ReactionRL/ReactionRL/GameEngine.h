#pragma once
#include <libtcod.hpp>
#include "Scene.h"

class GameEngine
{
public:
	TCOD_key_t key;
	TCOD_mouse_t mouse;
	ACTIVE_SCREEN screen;

	GameEngine();
	~GameEngine();

	void update(uint32 deltaTime);
	void render();
private:
	Scene *sceneList[2];
};

