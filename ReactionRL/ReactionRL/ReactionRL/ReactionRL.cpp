// REactionRL is an implementation of the Reaction ruleset using the Star Wars universe

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