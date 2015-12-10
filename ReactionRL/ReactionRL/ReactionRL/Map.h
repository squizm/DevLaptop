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
	float ambientLight;
	Tile* map[48][48];
	TCODRandom* random;
	TCODList<Player*> players;
	TCODList<Player*> lights;
	Map();
	~Map();
	void generateMap();
	void generateLights();
private:
	float distance(int x1, int y1, int x2, int y2);
	float clamp(float number, float min, float max);
	bool isInFoV(int x1, int y1, int x2, int y2);
};

