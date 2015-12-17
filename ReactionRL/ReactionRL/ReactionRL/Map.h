#pragma once
#include "Tile.h"
#include "Entity.h"
#include "Player.h"
#include <math.h>

class Map
{
public:
	int entityIDNum;
	Player* player;
	Tile* map[120][80];
	TCODRandom* random;
	TCODList<Entity*> game_objects;
	TCODImage* mapLights;
	int MAP_HEIGHT, MAP_WIDTH;

	//TCODList<Player*> lights;
	Map();
	~Map();
	void generateMap();
	TCODImage* generateLights();
private:
	float distance(int x1, int y1, int x2, int y2);
	float clamp(float number, float min, float max);
	bool isInLOS(int x1, int y1, int x2, int y2);
};

