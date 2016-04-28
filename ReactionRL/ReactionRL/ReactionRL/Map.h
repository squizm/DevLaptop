#pragma once
#include <libtcod.hpp>
#include <math.h>

#define TERRAIN_WATER 0.3f
#define TERRAIN_WATER_COLOR 255.0f
#define TERRAIN_BEACH 0.45f
#define TERRAIN_BEACH_COLOR 40.f
#define TERRAIN_GRASS 0.6f
#define TERRAIN_GRASS_COLOR 124.0f
#define TERRAIN_MOUNTAIN 0.8f
#define TERRAIN_MOUNTAIN_COLOR 30.0f

class Map
{
public:
	struct Tile
	{
		char img;
		bool isExplored;
		TCODColor fore;
		TCODColor back;
	};
	TCODMap* map;
	TCODHeightMap* heightMap;
	TCODConsole* mapImage;
	int width, height;
	Tile* tileArray[72][72];
	
	Map(int width, int height);
	~Map();
	void generateWorldMap();
	void generateLocalMap(short terrainType);
	void computeFOV(int x, int y, int radius);
	bool isEmpty(int x, int y);
	bool isInLOS(int x1, int y1, int x2, int y2);
	float distance(int x1, int y1, int x2, int y2);
private:
	float clamp(float number, float min, float max);
	void smoothMap();
	int getSurroundingWallCount(int x, int y);	
};