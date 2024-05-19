#pragma once
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "Input.h"

#include "SpaceShip.h"
#include "Slime.h"
#include "QuadTreev2.h"
using namespace std;

class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int x, int y, int width, int height);
	void HandleEvents();
	void Update(float deltaTime);
	void Render(float deltaTime);
	void Clean();

	bool IsRunning();

	static int ScreenWidth;
	static int ScreenHeight;

private:
	bool m_isRunning;
	Input* m_input;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	std::vector<GameObject*> m_collisionList;

	QuadTreev2* m_quadTreev2;


	Slime* m_enemy;
	Slime* m_enemy1;
	Slime* m_enemy2;
	Slime* m_enemy3;
	Slime* m_enemy4;
	Slime* m_enemy5;

	SpaceShip* m_player;

};

