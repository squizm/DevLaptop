#include <libtcod.hpp>
#include <gui/gui.hpp>
#include "GameObject.h"

bool running = true;
TCOD_key_t key;
TCOD_mouse_t mouse;
TCODConsole *osc;
GameObject *character;
TCODMap *map;

void update()
{
	TCOD_event_t event = TCODSystem::checkForEvent(TCOD_EVENT_ANY, &key, &mouse);
	if (event == TCOD_EVENT_KEY_RELEASE)
	{
		switch (key.vk){
		case TCODK_ESCAPE:
			running = false;
			break;
		}
	}
	mouse = TCODMouse::getStatus();
}

void render()
{
	// clear consoles
	TCODConsole::root->clear();
	osc->clear();

	//draw main map console
	osc->printFrame(0, 0, 65, 40, true, TCOD_BKGND_DEFAULT, "Main Map");
	osc->putChar(character->x, character->y, character->ch);
	osc->setCharBackground(mouse.cx, mouse.cy, TCODColor::red);
	TCODConsole::blit(osc, 0, 0, 65, 40, TCODConsole::root, 0, 0, 1.0f, 1.0f);
}

void init()
{
	//root console config
	TCODConsole::initRoot(80, 50, "ReactionRL", false);
	TCODSystem::setFps(60);

	//off screen console config
	osc = new TCODConsole(80, 50);
	osc->setDefaultBackground(TCODColor::darkestGrey);
	osc->setDefaultForeground(TCODColor::white);

	// temp character
	character = new GameObject(5, 5, '@');
}

int main()
{
	init();
	while (!TCODConsole::isWindowClosed() && running) {
		update();
		render();
		TCODConsole::flush();
	}
	return 0;
}