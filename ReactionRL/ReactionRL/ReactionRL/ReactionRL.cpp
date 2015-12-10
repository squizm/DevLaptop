// Brian Ancliffe 2015

#include "GameEngine.h"

int main()
{
	GameEngine *game = new GameEngine();
	while (running) {
		game->update();
		game->render();
	}
	return 0;
}