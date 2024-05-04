#pragma once
#include <SDL.h>
#include <stdio.h>
#include <iostream>
using namespace std;

class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int x, int y, int width, int height);
	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	bool IsRunning();

private:
	bool m_isRunning;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

};

