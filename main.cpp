#include <stdio.h>
#include <SDL.h>
#include "Game.h"

static float framePerSecondCounter = 0;

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

	//FPS
	float elapsedTime = 0;
	Uint64 frameCount = 0;
	framePerSecondCounter = 0;

	game = new Game();
	game->Init("Prototype", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768);
	while (game->IsRunning())
	{
		frameCount++;
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
		deltaTime = (tickTime - lastTime)/1000.0f;
		lastTime = tickTime;

		//FPS Calculation
		elapsedTime += SDL_GetTicks64() - frameStart;
		if (elapsedTime >= 1000.0f)
		{
			framePerSecondCounter = frameCount / (elapsedTime / 1000.0f);
			game->PassFPSValue(framePerSecondCounter);
			elapsedTime = 0;
			frameCount = 0;
		}
	}

	game->Clean();

	return 0;
}
