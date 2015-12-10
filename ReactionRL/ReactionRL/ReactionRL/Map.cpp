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
	lights.clearAndDelete();
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

	TCODImage * mapLights = new TCODImage("BG_lights2.png");
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
			// set each tile to ambientLight level
			tile->luminosity = ambientLight;
			tile->tintColor = tile->backColor;

			// loop through each player and multiplicatively add their luminosity if tile is in FOV
			for (auto& obj : players)
			{
				if (isInFoV(obj->x, obj->y, tile->x, tile->y))
				{
					float distanceToPlayer = distance(obj->x, obj->y, tile->x, tile->y);
					float playerLuminosityAtTile = 1.0f - distanceToPlayer / obj->FoV;
					tile->luminosity += float(fmax(0.0f, playerLuminosityAtTile));
				}
			}

			// loops through each light and add its luminosity and color tint
			for (auto& light : lights)
			{
				if (isInFoV(light->x, light->y, tile->x, tile->y))
				{
					float distanceToLight = distance(light->x, light->y, tile->x, tile->y);
					float lightLuminosityAtTile = 1.0f - distanceToLight / light->FoV;
					tile->luminosity += float(fmax(0.0f, lightLuminosityAtTile));
					tile->tintColor = tile->tintColor + (light->color * lightLuminosityAtTile);
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
	return float(sqrt(dx*dx + dy*dy));	
}

float Map::clamp(float number, float min, float max)
{
	return (number < 0.0f) ? 0.0f : (number > 1.0f) ? 1.0f : number;
}