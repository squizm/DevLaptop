// Brian Ancliffe 2015

#include "GameEngine.h"

int main()
{
	GameEngine *game = new GameEngine();
	uint32 oldTime = TCODSystem::getElapsedMilli();
	uint32 currTime = oldTime;
	while (running) {
		oldTime = currTime;
		currTime = TCODSystem::getElapsedMilli();
		game->update(currTime - oldTime);
		game->render();
	}
	return 0;
}