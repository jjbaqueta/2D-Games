#include <iostream>
#include "./Constants.h"
#include "./Game.h"

// Global variables used to set rectangle position and its move speed
float projectilePosX = 0.0f;
float projectilePosY = 0.0f;
float projectileVelX = 0.25f;
float projectileVelY = 0.25f;

Game::Game()
{
	this->running = false;
}

Game::~Game(){}

bool Game::isRunning() const
{
	return this->running;
}

void Game::initialize(int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Error initializing SDL." << std::endl;
		return;
	}

	// Creating the view window 
	window = SDL_CreateWindow
	(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_BORDERLESS
	);

	if (!window)
	{
		std::cerr << "Error creating SDL window." << std::endl;
		return;
	}

	// Creating the renderer using the default display driver (parameter -1)
	renderer = SDL_CreateRenderer(window, -1, 0);

	if(!renderer)
	{
		std::cerr << "Error creating SDL renderer." << std::endl;
		return;
	}

	running = true;
}

void Game::processingInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT: // Ends the application when the window is closed
		{
			running = false;
			break;
		}
		case SDL_KEYDOWN: // Ends the application when the escape key (ESC) is pressed
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				running = false;
			}
		}
		default:
		{
			break;
		}
	}
}

void Game::update()
{
	// Updating X and Y positions according to velocities parameters
	projectilePosX += projectileVelX;
	projectilePosY += projectileVelY;
}

void Game::render()
{
	// Setting the background color of screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// Cleaning the current visualization
	SDL_RenderClear(renderer);

	// Creating a small white rectangle which going to move through screen
	SDL_Rect rectangle;

	rectangle.x = (int) projectilePosX;
	rectangle.y = (int) projectilePosY;
	rectangle.w = 10;
	rectangle.h = 10;

	// Setting rectangle's color
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// Rendering the rectangle
	SDL_RenderFillRect(renderer, &rectangle);
	SDL_RenderPresent(renderer);
}

void Game::destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

