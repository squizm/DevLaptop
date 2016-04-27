#include "SceneCampaign.h"
#include <random>
#include <functional>

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0, MAP_WIDTH - 1);
auto mapRoller = std::bind(distribution, generator);

SceneCampaign::SceneCampaign(int width, int height): width(width), height(height)
{
	map = new Map(MAP_WIDTH, MAP_HEIGHT);
	map->generateLocalMap(0);

	for (int i = 0; i < MAX_CHARACTERS; i++)
	{
		int x, y = 0;
		do
		{
			x = mapRoller();
			y = mapRoller();
		} while (map->isEmpty(x, y) != true);
		characters[i] = new Character(x, y, '@', 12);
	}
	characters[0]->isPlayer = true;
	player = characters[0];
	map->map->computeFov(player->x, player->y, player->FoV);
}

SceneCampaign::~SceneCampaign()
{
	delete map;
}

void SceneCampaign::update(TCOD_event_t e, TCOD_mouse_t m, TCOD_key_t k, uint32 delta)
{
	evt = e;
	mouse = m;
	key = k;
	if (e == TCOD_EVENT_KEY_RELEASE)
	{
		switch (key.vk) {
		case TCODK_ESCAPE:
			break;
		case TCODK_UP:
			if(map->isEmpty(player->x, player->y -1))
				player->y -= 1;
			break;
		case TCODK_DOWN:
			if (map->isEmpty(player->x, player->y + 1))
				player->y += 1;
			break;
		case TCODK_LEFT:
			if (map->isEmpty(player->x - 1, player->y))
				player->x -= 1;
			break;
		case TCODK_RIGHT:
			if (map->isEmpty(player->x + 1, player->y))
				player->x += 1;
			break;
		default:
			break;
		}
	}
	map->computeFOV(player->x, player->y, player->FoV);
}

void SceneCampaign::render(TCODConsole *console)
{
	for (int x = 0; x < map->width; x++)
	{
		for (int y = 0; y < map->height; y++)
		{
			if (map->map->isInFov(x, y))
				(map->map->isWalkable(x, y)) ? console->putCharEx(x, y, '.', TCODColor::white, TCODColor::black) : console->putCharEx(x, y, '#', TCODColor::white, TCODColor::black);
			else
				(map->map->isWalkable(x, y)) ? console->putCharEx(x, y, '.', TCODColor::darkerGrey, TCODColor::black) : console->putCharEx(x, y, '#', TCODColor::darkerGrey, TCODColor::black);
		}
	}

	for (Character* character : characters)
	{
		if (map->map->isInFov(character->x, character->y))
		{
			if(character == player)
				console->putCharEx(character->x, character->y, character->img, TCODColor::green, TCODColor::black);
			else
				console->putCharEx(character->x, character->y, character->img, TCODColor::red, TCODColor::black);
		}
		else
		{
			console->putCharEx(character->x, character->y, character->img, TCODColor::darkerGrey, TCODColor::black);
		}
	}
}