#include "Map.h"

Map::Map()
{
	random = TCODRandom::getInstance();
}

Map::~Map()
{
	for (auto  elem : map)
		delete elem;

	objects.clearAndDelete();
}

void Map::generateMap()
{
	for (auto& tile : map)
	{
		delete tile;
	}

	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			map[x + y * MAP_WIDTH] = new Tile(x, y, ' ', TCODColor::white, TCODColor::white, Tile::TILE_TYPE::Transparent | Tile::TILE_TYPE::Walkable);
		}
	}

	// load test map
	TCODImage *pic = new TCODImage("BG_dungeon.png");
	int width, height;
	pic->getSize(&width, &height);
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			TCODColor pxl = pic->getPixel(x, y);
			if (pxl == TCODColor::black)
			{
				map[x + y * MAP_WIDTH]->flags = Tile::TILE_TYPE::Blocking | Tile::TILE_TYPE::Opaque;
			}
			else
			{
				map[x + y * MAP_WIDTH]->flags = Tile::TILE_TYPE::Walkable | Tile::TILE_TYPE::Transparent;
			}
			map[x + y * MAP_WIDTH]->backColor = pxl;
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
		if (map[curX + curY * MAP_WIDTH]->flags == Tile::TILE_TYPE::Opaque)
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