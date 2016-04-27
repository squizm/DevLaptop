#include "GameEngine.h"
#include "SceneMainMenu.h"
#include "SceneGameplay.h"
#include "SceneCampaign.h"

GameEngine::GameEngine()
{
	//root console config
	TCODConsole::initRoot(120, 80, "ThoriumBREED", false, TCOD_RENDERER_SDL);
	TCODSystem::setFps(60);

	//Setup Scenes
	sceneList[MAINMENU] = new SceneMainMenu(TCODConsole::root->getWidth(), TCODConsole::root->getHeight());
	sceneList[CAMPAIGN] = new SceneCampaign(TCODConsole::root->getWidth(), TCODConsole::root->getHeight());
	sceneList[TGEN] = new SceneGameplay(TCODConsole::root->getWidth(), TCODConsole::root->getHeight());
	activeScene = MAINMENU;

	TCODConsole::root->setDefaultBackground(TCODColor::black);
}

GameEngine::~GameEngine()
{
	for (auto& scene : sceneList)
		delete scene;
}

void GameEngine::update(uint32 deltaTime)
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
	sceneList[activeScene]->update(event, mouse, key, deltaTime);
}

void GameEngine::render()
{
	TCODConsole::root->clear();
	sceneList[activeScene]->render(TCODConsole::root);
	TCODConsole::root->flush();
}