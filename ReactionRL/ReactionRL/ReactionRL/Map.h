#pragma once
#include "Tile.h"
#include "Entity.h"
#include <math.h>

#define MAP_WIDTH 120
#define MAP_HEIGHT 80

class Map
{
public:
	Tile* map[MAP_WIDTH * MAP_HEIGHT];
	TCODRandom* random;
	TCODList<Entity*> objects;

	Map();
	~Map();
	void generateMap();
private:
	float distance(int x1, int y1, int x2, int y2);
	float clamp(float number, float min, float max);
	bool isInLOS(int x1, int y1, int x2, int y2);
};

