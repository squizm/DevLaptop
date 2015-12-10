#include "SceneMainMenu.h"


void btnFullscreen()
{
	TCODConsole::setFullscreen(!TCODConsole::isFullscreen());
}

void btnGameplay()
{
	for (int fade = 255; fade >= 0; fade -= 10 ) {
		TCODConsole::setFade(fade, TCODColor::black);
		TCODConsole::flush();
	}
	activeScene = 1;
	TCODConsole::setFade(255, TCODColor::black);
}

void btnExit()
{
	running = false;
}


void SceneMainMenu::update(TCOD_event_t e, TCOD_mouse_t m, TCOD_key_t k)
{
	evt = e;
	mouse = m;
	key = k;
	if (e == TCOD_EVENT_KEY_RELEASE)
	{
		switch (key.vk){
		case TCODK_ESCAPE:
			//running = false;
			break;
		default:
			break;
		}
	}
	for (int i = 0; i < numButtons; i++)
	{
		buttons[i]->update(e, m, k);
	}
}

void SceneMainMenu::render(TCODConsole *console)
{
	console->setDefaultBackground(TCODColor::black);
	for (int i = 0; i < numButtons; i++)
	{
		buttons[i]->render(console);
	}
	console->print(width/2 - 6, height/2 - 5, "ThoriumBREED");
}

SceneMainMenu::SceneMainMenu(int w, int h)
{
	width = w;
	height = h;
	numButtons = 3;
	buttons[0] = new Button(1, 1, "+", btnFullscreen);
	buttons[1] = new Button(w/2 - 5, h/2 + 3, "Gameplay", btnGameplay);
	buttons[2] = new Button(w/2 - 3, h/2 + 11, "Exit", btnExit);
}

SceneMainMenu::~SceneMainMenu()
{
	for (int i = 0; i < numButtons; i++)
	{
		delete buttons[i];
	}
}

