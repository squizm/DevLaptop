#include "SceneMainMenu.h"


void btnFullscreen()
{
	TCODConsole::setFullscreen(!TCODConsole::isFullscreen());
}

void btnGameplay()
{
	for (int fade = 255; fade >= 0; fade -= 10 ) {
		TCODConsole::root->setFade(fade, TCODColor::black);
		TCODConsole::root->flush();
	}
	activeScene = ACTIVE_SCREEN::TGEN;
	TCODConsole::root->setFade(255, TCODColor::black);
}

void btnCampaign()
{
	activeScene = ACTIVE_SCREEN::CAMPAIGN;
}

void btnExit()
{
	running = false;
}


void SceneMainMenu::update(TCOD_event_t e, TCOD_mouse_t m, TCOD_key_t k, uint32 delta)
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
	for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++)
	{
		buttons[i]->update(e, m.cx, m.cy, k, delta);
	}
}

void SceneMainMenu::render(TCODConsole *console)
{
	for (int i = 0; i < sizeof(buttons)/sizeof(buttons[0]); i++)
	{
		buttons[i]->render(console);
	}
	console->print(width/2 - 6, height/2 - 5, "ThoriumBREED");
}

SceneMainMenu::SceneMainMenu(int w, int h)
{
	width = w;
	height = h;
	buttons[0] = new Button(1, 1, "+", btnFullscreen);
	buttons[1] = new Button(w/2 - 2, h/2 + 3, "TGen", btnGameplay);
	buttons[2] = new Button(w / 2 - 4, h / 2 + 7, "Campaign", btnCampaign);
	buttons[3] = new Button(w/2 - 2, h/2 + 11, "Exit", btnExit);
}

SceneMainMenu::~SceneMainMenu()
{
	for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++)
	{
		delete buttons[i];
	}
}

