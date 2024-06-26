#include "Perspective.h" 
#include "Settings.h"  //apagar

int main(int argc, char* args[]) {
	Perspective* game = new Perspective();

	if (game->init("Perspective projection")) {
		SDL_ShowCursor(SDL_DISABLE);
		while (game->running()) {
			game->handleEvents();
			game->update();
		}
	}

	game->clean();
	delete game;

	return 0;
}

