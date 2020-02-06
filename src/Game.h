#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Game
{
	private:
		bool running;
		int ticksLastFrame;
		SDL_Window *window;
		SDL_Renderer *renderer;

	public:
		Game();
		~Game();
		bool isRunning() const;
		void initialize(int width, int hight);	// Creates the game window
		void processingInput();					// Processes all inputs
		void update();							// Updates the game elements
		void render();							// Draws the elements into window
		void destroy();							// Destroys SDL elements
};

#endif
