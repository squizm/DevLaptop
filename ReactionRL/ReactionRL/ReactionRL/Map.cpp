#include "Map.h"


Map::Map()
{
	random = TCODRandom::getInstance();
	entityIDNum = 0;
	ambientLight = 0.5f;
	player = new Player(7, 30, TCOD_CHAR_SMILIE, TCODColor::green, true, 24, 0);
	players.push(player);
}


Map::~Map()
{
	for (auto  elem : map)
		delete elem;

	players.clearAndDelete();
}

void Map::generateMap()
{
	for (auto& elem : map)
	{
		for (auto& tile : elem)
		{
			delete tile;
		}
	}

	for (int x = 0; x < 48; x++)
	{
		for (int y = 0; y < 48; y++)
		{
			map[x][y] = new Tile(x, y, ' ', TCODColor::white, TCODColor::white, true, true);
		}
	}

	// load test map
	TCODImage *pic = new TCODImage("BG.png");
	int width, height;
	pic->getSize(&width, &height);
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			TCODColor pxl = pic->getPixel(x, y);
			if (pxl == TCODColor::black)
			{
				map[x][y]->isWalkable = false;
				map[x][y]->isTransparent = false;
			}
			else
			{
				map[x][y]->isWalkable = true;
				map[x][y]->isTransparent = true;
			}
			map[x][y]->backColor = pxl;
		}
	}

	TCODImage *mapLights = new TCODImage("BG_lights2.png");
	mapLights->getSize(&width, &height);
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (mapLights->getPixel(x, y) != TCODColor::black)
			{
				lights.push(new Player(x, y, ' ', mapLights->getPixel(x, y),1, 10, ++entityIDNum));
			}
		}
	}
}

void Map::generateLights()
{
	for (auto& row : map)
	{
		for (auto& tile : row)
		{
			tile->luminosity = ambientLight;
		}
	}
	for (auto& obj : players)
	{
		for (auto& row : map)
		{
			for (auto& tile : row)
			{
				if (isInFoV(obj->x, obj->y, tile->x, tile->y))
				{
					float dist = distance(obj->x, obj->y, tile->x, tile->y);
					float tempLuminosity = 1.0f - dist / obj->FoV;
					if (tempLuminosity > 0)
						tile->luminosity += tempLuminosity;
				}
			}
		}
	}

	for (auto& obj : lights)
	{
		for (auto& row : map)
		{
			for (auto& tile : row)
			{
				if (isInFoV(obj->x, obj->y, tile->x, tile->y))
				{
					float dist = distance(obj->x, obj->y, tile->x, tile->y);
					float tempLuminosity = 1.0f - dist / (obj->FoV+obj->flicker);
					if (tempLuminosity > 0)
						tile->luminosity += tempLuminosity;
					tile->tintColor = tile->tintColor * obj->col;
				}
			}
		}
	}

}

bool Map::isInFoV(int x1, int y1, int x2, int y2)
{
	TCODLine::init(x1, y1, x2, y2);
	int curX = x1;
	int curY = y1;
	do
	{
		if (!map[curX][curY]->isTransparent)
			return false;
	} while (!TCODLine::step(&curX, &curY));
	return true;
}

float Map::distance(int x1, int y1, int x2, int y2)
{
	float dx = (float)x1 - x2;
	float dy = (float)y1 - y2;
	return sqrt(dx*dx + dy*dy);	
}

float Map::clamp(float number, float min, float max)
{
	return (number < 0.0f) ? 0.0f : (number > 1.0f) ? 1.0f : number;
}