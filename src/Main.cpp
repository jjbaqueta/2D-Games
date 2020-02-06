#include <iostream>
#include "./Game.h"
#include "./Constants.h"

int main(int argc, char *args[])
{
	Game *game = new Game();
	game->initialize(WINDOW_WIDTH, WINDOW_HIGHT);
	
	/*
	 * Basic game loop
	 * Updates the game elements while the game is running 
	 */
	while (game->isRunning())
	{
		game->processingInput();
		game->update();
		game->render();
	}

	game->destroy();

	return 0;
}

