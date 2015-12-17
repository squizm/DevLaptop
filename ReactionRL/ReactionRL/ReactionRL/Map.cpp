#include "Map.h"

Map::Map()
{
	random = TCODRandom::getInstance();
	entityIDNum = 0;
	player = new Player();
	player->setEntityInfo(20, 15, TCOD_CHAR_SMILIE_INV, TCODColor::darkestGreen, 0, 50,  ENTITY_TYPE::character);
	game_objects.push(player);
	MAP_HEIGHT = 80;
	MAP_WIDTH = 120;
	mapLights = new TCODImage(MAP_WIDTH, MAP_HEIGHT);
	mapLights->setKeyColor(TCODColor::purple);
}

Map::~Map()
{
	for (auto  elem : map)
		delete elem;

	game_objects.clearAndDelete();
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

	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			map[x][y] = new Tile(x, y, ' ', TCODColor::white, TCODColor::white, Tile::solid, true, true);
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
				map[x][y]->isWalkable = false;
				map[x][y]->isTransparent = false;
			}
			else
			{
				map[x][y]->isWalkable = true;
				map[x][y]->isTransparent = true;
			}
			map[x][y]->backColor = pxl;
			map[x][y]->foreColor = pxl;
		}
	}

	TCODImage * mapLights = new TCODImage("BG_dungeon_lights.png");
	mapLights->getSize(&width, &height);
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (mapLights->getPixel(x, y) != TCODColor::black)
			{
				Player* light = new Player();
				light->setEntityInfo(x, y, ' ', mapLights->getPixel(x, y), ++entityIDNum, 32, ENTITY_TYPE::light);
				game_objects.push(light);
			}
		}
	}
}

TCODImage* Map::generateLights()
{
	mapLights->clear(TCODColor::purple);
	Tile tempTile = Tile(-1,-1,' ', TCODColor::white, TCODColor::white, Tile::solid, true, true);
	map[player->x][player->y]->isTransparent = false;
	for (auto& row : map)
	{
		for (auto& tile : row)
		{
			// set each tile to ambientLight level
			tempTile = *tile;
			tempTile.luminosity = 0.5f;
			tempTile.tintColor = tempTile.backColor;

			if (tempTile.x == player->x && tempTile.y == player->y)
				map[player->x][player->y]->isTransparent = true;
			else
				map[player->x][player->y]->isTransparent = false;
			// loop through each player and if tile is in LOS adjust lighting
			for (auto& obj : game_objects)
			{
				if (obj->type == ENTITY_TYPE::character)
				{
					if (isInLOS(obj->x, obj->y, tempTile.x, tempTile.y))
					{
						float distanceToPlayer = distance(obj->x, obj->y, tempTile.x, tempTile.y);
						if (distanceToPlayer <= obj->FoV)
						{
							tempTile.luminosity = fmax((1.0f - (distanceToPlayer / obj->FoV)), tempTile.luminosity);
						}
					}
				}
				if (obj->type == ENTITY_TYPE::light)
				{
					if (isInLOS(obj->x, obj->y, tempTile.x, tempTile.y)) // is the tile in the lights line of sight?
					{
						float distanceToLight = distance(obj->x, obj->y, tempTile.x, tempTile.y); // distance from the tile to the light
						if (distanceToLight <= obj->FoV) // if the tile is the lights radius
						{
							tempTile.luminosity = fmax((1.0f - (distanceToLight / obj->FoV)), tempTile.luminosity);
							//add the light's color to the tile
							//tempTile.tintColor = TCODColor::lerp(tempTile.tintColor, light->color,fmax(0.0f, 1.0f - (distanceToLight / light->FoV))); 
						}
					}
				}
			}
			mapLights->putPixel(tempTile.x, tempTile.y, tempTile.tintColor * tempTile.luminosity);
		}
	}
	return mapLights;
}

bool Map::isInLOS(int x1, int y1, int x2, int y2)
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
	return (number < min) ? min : (number > max) ? max : number;
}