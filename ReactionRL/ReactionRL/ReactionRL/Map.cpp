#include "Map.h"
#include <random>
#include <functional>

std::default_random_engine gen;
std::uniform_int_distribution<int> dist(0, 99);
auto d100 = std::bind(gen, dist);

Map::Map(int width, int height): width(width), height(height)
{
	map = new TCODMap(width, height);
	heightMap = new TCODHeightMap(width, height);
	mapImage = new TCODConsole(width, height);
	
	// Create tiles
	for (int x = 0; x < 72; x++)
	{
		for (int y = 0; y < 72; y++)
		{
			tileArray[x][y] = new Tile();
			tileArray[x][y]->isExplored = false;
			tileArray[x][y]->img = '.';
			tileArray[x][y]->fore = TCODColor::darkGreen;
			tileArray[x][y]->back = TCODColor::darkestGreen;
		}
	}
}

Map::~Map()
{
	map->~TCODMap();
}

void Map::generateWorldMap()
{
	map->clear(true, true);
	heightMap->clear();

	// add FBM noise 0.0f to 1.0f
	heightMap->addFbm(new TCODNoise(2, TCOD_NOISE_SIMPLEX),5.0f, 5.0f, 0.3f, 0.3f, 30.0f, 0.5f, 0.3f);
	heightMap->normalize();

	// Islandize noise
	for (int x = 0; x < heightMap->w; x++)
	{
		for (int y = 0; y < heightMap->h; y++)
		{	
			float newVal = heightMap->getValue(x, y) * (0.6f - (distance(x, y, heightMap->w / 2, heightMap->h / 2) / heightMap->w));
			heightMap->setValue(x, y, newVal);
		}
	}
	heightMap->normalize();
	
	for (int x = 0; x < heightMap->w; x++)
	{
		for (int y = 0; y < heightMap->h; y++)
		{
			float value = heightMap->getValue(x, y);
			if(value < TERRAIN_WATER)
				mapImage->putCharEx(x, y, '~', TCODColor(TERRAIN_WATER_COLOR, 0.75f, value), TCODColor(TERRAIN_WATER_COLOR, 0.75f, value));
			else if (value < TERRAIN_BEACH)
				mapImage->putCharEx(x, y, '.', TCODColor(TERRAIN_BEACH_COLOR, 0.75f, value),TCODColor(TERRAIN_BEACH_COLOR, 0.75f, value));
			else if (value < TERRAIN_GRASS)
				mapImage->putCharEx(x, y, '"', TCODColor(TERRAIN_GRASS_COLOR, 0.75f, value), TCODColor(TERRAIN_GRASS_COLOR, 0.75f, value));
			else 
				mapImage->putCharEx(x, y, '^', TCODColor(TERRAIN_MOUNTAIN_COLOR, 0.1f, value), TCODColor(TERRAIN_MOUNTAIN_COLOR, 0.1f, value));
		}
	}
}

bool Map::isInLOS(int x1, int y1, int x2, int y2)
{
	TCODLine::init(x1, y1, x2, y2);
	int curX = x1;
	int curY = y1;
	do
	{
		if (!map->isTransparent(curX, curY))
			return false;
	} while (!TCODLine::step(&curX, &curY));
	return true;
}

float Map::distance(int x1, int y1, int x2, int y2)
{
	float dx = (float)x1 - x2;
	float dy = (float)y1 - y2;
	return float(sqrt(dx*dx + dy*dy));	
}

float Map::clamp(float number, float min, float max)
{
	return (number < min) ? min : (number > max) ? max : number;
}

void Map::computeFOV(int x, int y, int radius)
{
	map->computeFov(x, y, radius);
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (map->isInFov(x, y))
			{
				tileArray[x][y]->isExplored = true;
			}
		}
	}
}

void Map::generateLocalMap(short terrainType)
{
	map->clear();
	memset(tileArray, 0, sizeof(tileArray));
	short fillPercentage = 45;
	for (int x = 0; x < width ; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
			{
				map->setProperties(x, y, false, false);
				map->setProperties(x, y, false, false);
				tileArray[x][y] = new Tile();
				tileArray[x][y]->isExplored = false;
				tileArray[x][y]->img = '#';
				tileArray[x][y]->fore = TCODColor::sepia;
				tileArray[x][y]->back = TCODColor::darkestSepia;
			}
			else
			{
				if (dist(gen) < fillPercentage)
				{
					map->setProperties(x, y, false, false);
					tileArray[x][y] = new Tile();
					tileArray[x][y]->isExplored = false;
					tileArray[x][y]->img = '#';
					tileArray[x][y]->fore = TCODColor::white;
					tileArray[x][y]->back = TCODColor::darkestSepia;
				}
				else
				{
					map->setProperties(x, y, true, true);
					tileArray[x][y] = new Tile();
					tileArray[x][y]->isExplored = false;
					tileArray[x][y]->img = '.';
					tileArray[x][y]->fore = TCODColor::darkGreen;
					tileArray[x][y]->back = TCODColor::darkestGreen;
				}
			}
		}
	}
	smoothMap();
}

void Map::smoothMap()
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int neighbourWallTiles = getSurroundingWallCount(x, y);
			if (neighbourWallTiles > 4)
			{
				map->setProperties(x, y, false, false);
				tileArray[x][y]->img = '#';
				tileArray[x][y]->fore = TCODColor::white;
				tileArray[x][y]->back = TCODColor::darkestSepia;
			}
			else if (neighbourWallTiles < 4)
			{
				map->setProperties(x, y, true, true);
				tileArray[x][y]->img = '.';
				tileArray[x][y]->fore = TCODColor::darkGreen;
				tileArray[x][y]->back = TCODColor::darkestGreen;
			}
		}
	}
}

int Map::getSurroundingWallCount(int x, int y)
{
	int wallCount = 0;
	for (int neighbourX = x - 1; neighbourX <= x + 1; neighbourX++) {
		for (int neighbourY = y - 1; neighbourY <= y + 1; neighbourY++) {
			if (neighbourX >= 0 && neighbourX < height && neighbourY >= 0 && neighbourY < height) {
				if (neighbourX != x || neighbourY != y) {
					wallCount += !map->isWalkable(neighbourX,neighbourY);
				}
			}
			else {
				wallCount++;
			}
		}
	}
	return wallCount;
}

bool Map::isEmpty(int x, int y)
{
	return map->isWalkable(x, y);
}