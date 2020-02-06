#include <iostream>
#include "./Constants.h"
#include "./Game.h"

/* Global variables used to set rectangle position and its move speed
 * The value of velocity parameter must be defined in pixel per frame
 * Velocity: in how many pixels is object going to move since current frame up to next frame?
 */
float projectilePosX = 0.0f;
float projectilePosY = 0.0f;
float projectileVelX = 50.0f;
float projectileVelY = 60.0f;

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
	// Wait until 16ms has ellapsed since the last frame (for faster machines)
	while(!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));

	/* 
	 * Delta time is the difference in ticks from last frame converted to seconds
	 * It represents the time passed since the last frame updating until now (in seconds)
	 */
	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

	// Clamp deltaTime to a maximum value (for slower  machines)
	deltaTime = (deltaTime > 0.05f) ? 0.05 : deltaTime;

	// Update ticksLastFrame with current frame time
	ticksLastFrame = SDL_GetTicks();

	/*
	 * The objects are going to move according to an elapsed time, 
	 * instead to use the clock cycle from computer
	 */
	projectilePosX += projectileVelX * deltaTime;
	projectilePosY += projectileVelY * deltaTime;
}

void Game::render()
{
	// Setting the background color of screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// Cleaning the current visualization
	SDL_RenderClear(renderer);

	// Creating a small white rectangle which is going to move through screen
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

