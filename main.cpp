#include <stdio.h>
#include <SDL.h>
#include "Game.h"


int main(int argc, char* arg[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint64 frameStart;
	Uint64 frameTime = 0;
	float deltaTime = 0.0;
	float lastTime = 0.0;
	float tickTime = 0.0;
	Game* game = nullptr;


	game = new Game();
	game->Init("Prototype", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768);
	while (game->IsRunning())
	{
		frameStart = SDL_GetTicks64();
		game->HandleEvents();
		game->Update(deltaTime);
		game->Render(deltaTime);
		frameTime = SDL_GetTicks64() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
		tickTime = SDL_GetTicks64();
		deltaTime = (tickTime - lastTime)/1000.0;
		lastTime = tickTime;
	}

	game->Clean();

	return 0;
}
