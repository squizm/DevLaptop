#include "SceneCampaign.h"
#include <random>
#include <functional>
#include <sstream>

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0, MAP_WIDTH - 1);
auto mapRoller = std::bind(distribution, generator);

SceneCampaign::SceneCampaign(int width, int height): width(width), height(height)
{
	map = new Map(MAP_WIDTH, MAP_HEIGHT);
	map->generateLocalMap(0);

	generateCharacters();

	menuConsole = new TCODConsole(48, 80);
	menuConsole->printFrame(0, 0, 48, 80);

	popup = new Popup(POPUP_NOTIFICATION, "Pop up!", (width/2) - (MAX_WIDTH/2), height/2, "this is a test. this is a test.");
	popup->isShown = false;

	log.clear();
}

SceneCampaign::~SceneCampaign()
{
	delete map;
	delete popup;
}

void SceneCampaign::generateCharacters()
{
	log.push_back("Generating Characters");
	memset(characters, 0, sizeof(characters));
	for (int i = 0; i < MAX_CHARACTERS; i++)
	{
		int x, y = 0;
		do
		{
			x = mapRoller();
			y = mapRoller();
		} while (map->isEmpty(x, y) != true);
		characters[i] = new Character(x, y, TCOD_CHAR_SMILIE, 16);
	}
	characters[0]->isPlayer = true;
	player = characters[0];
	player->path = new TCODPath(map->map);
	map->map->computeFov(player->x, player->y, player->FoV);
}

void SceneCampaign::update(TCOD_event_t e, TCOD_mouse_t m, TCOD_key_t k, uint32 delta)
{
	#pragma region Check Input
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
		case TCODK_SPACE:
			log.push_back("Generating new map");
			map->generateLocalMap(0);
			generateCharacters();
			break;
		default:
			break;
		}

		switch (key.c)
		{
		case 'p':
			popup->isShown = !popup->isShown;
			break;
		}
		map->computeFOV(player->x, player->y, player->FoV);
	}
	else if (e == TCOD_EVENT_MOUSE_RELEASE)
	{
		if (mouse.rbutton_pressed && mouse.cx < map->width && mouse.cy < map->height && (map->map->isInFov(mouse.cx, mouse.cy) || map->tileArray[mouse.cx][mouse.cy]->isExplored))
		{
			player->destX = mouse.cx;
			player->destY = mouse.cy;
			player->path->compute(player->x, player->y, player->destX, player->destY);
			log.push_back("Player moving");
		}
	}
	else if (e == TCOD_EVENT_MOUSE_MOVE)
	{
		menuConsole->clear();
		menuConsole->print(1, 1, "Mouse: %i,%i", mouse.cx, mouse.cy);
	}
	#pragma endregion

	#pragma region Game Actions
	if (!player->path->isEmpty())
	{
		if (player->x != player->destX || player->y != player->destY)
		{
			player->path->walk(&player->x, &player->y, false);
			map->computeFOV(player->x, player->y, player->FoV);
		}
	}
	#pragma endregion

	popup->update(e, m, k, delta);
	menuConsole->print(1, 78, "%i fps", TCODSystem::getFps());
}

void SceneCampaign::render(TCODConsole *console)
{
	// Draw Map
	for (int y = 0; y < map->width; y++)
	{
		for (int x = 0; x < map->height; x++)
		{
			if (map->map->isInFov(x, y))
				console->putCharEx(x, y, map->tileArray[x][y]->img, map->tileArray[x][y]->fore, map->tileArray[x][y]->back);
			else if (map->tileArray[x][y]->isExplored)
				console->putCharEx(x, y, map->tileArray[x][y]->img, TCODColor::white, TCODColor::black);
		}
	}

	// Draw Characters
	for (Character* character : characters)
	{
		if (map->map->isInFov(character->x, character->y))
			console->putCharEx(character->x, character->y, character->img, TCODColor::red, TCODColor::darkestRed);
	}
	console->putCharEx(player->x, player->y, player->img, TCODColor::white, TCODColor::black);

	// Draw Menu console
	console->blit(menuConsole, 0, 0, menuConsole->getWidth(), menuConsole->getHeight(), console, 72, 0);

	// Draw popup console
	if (popup->isShown)
	{
		popup->render();
		console->blit(popup->console, 0, 0, popup->width, popup->height, console, popup->locX, popup->locY, 1.0f, 0.75f);
	}
	
	// Draw message log
	float colourCoef = 1.0f;
	for (int i = 0; i < 5; i++)
	{
		if (log.size() > i)
		{
			TCODConsole::root->setDefaultForeground(TCODColor::white * colourCoef);
			console->printEx(1, 74 + i, TCOD_BKGND_DEFAULT, TCOD_alignment_t::TCOD_LEFT, log.at(i));
			colourCoef -= 0.2f;
		}
	}
	TCODConsole::root->setDefaultForeground(TCODColor::white);
}