#include "GameEngine.h"

GameEngine::GameEngine()
{
	//root console config
	TCODConsole::initRoot(160, 100, "ThoriumBREED", false, TCOD_RENDERER_GLSL);
	TCODSystem::setFps(60);
	this->console = TCODConsole::root;

	//Setup Scenes
	sceneList[MAINMENU] = new SceneMainMenu(this->console->getWidth(), this->console->getHeight());
	sceneList[GAMEPLAY] = new SceneGameplay(this->console->getWidth(), this->console->getHeight());
	activeScene = 0;

	state = MAINMENU;
}

GameEngine::~GameEngine()
{
	for (auto& scene : sceneList)
		delete scene;

	delete console;
}

void GameEngine::update()
{
	// Check for windows closed event
	if (TCODConsole::isWindowClosed())
	{
		running = false;
		return;
	}

	// Handle system events
	TCOD_event_t event = TCODSystem::checkForEvent(TCOD_EVENT_ANY, &key, &mouse);
	if (event == TCOD_EVENT_KEY_RELEASE)
	{
		switch (key.vk){
		case TCODK_ESCAPE:
			activeScene = MAINMENU;
			break;
		case TCODK_F11:
			TCODConsole::setFullscreen(!TCODConsole::isFullscreen());
			break;
		}
	}
	// Populate mouse data
	mouse = TCODMouse::getStatus();

	//Send info key and mouse states to active scene
	sceneList[activeScene]->update(event, mouse, key);
}

void GameEngine::render()
{
	this->console->clear();
	sceneList[activeScene]->render(this->console);	
	console->flush();
}