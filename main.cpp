#include <stdio.h>
#include <SDL.h>
#include "Game.h"


Game* game = nullptr;

int main(int argc, char* arg[])
{
	game = new Game();
	game->Init("Prototype", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768);
	while (game->IsRunning())
	{
		game->HandleEvents();
		game->Update();
		game->Render();
	}

	game->Clean();

	return 0;
}
