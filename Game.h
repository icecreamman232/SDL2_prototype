#pragma once
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "Input.h"
#include "AssetManager.h"

#include "SpaceShip.h"
#include "Slime.h"
#include "QuadTreev2.h"
#include "PlayerHealthBar.h"

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
	static SDL_Renderer* Renderer;

private:
	bool m_isRunning;
	Input* m_input;
	SDL_Window* m_window;

	std::vector<GameObject*> m_collisionList;

	QuadTreev2* m_quadTreev2;

	Slime* m_enemy;
	Slime* m_enemy1;
	Slime* m_enemy2;
	Slime* m_enemy3;
	Slime* m_enemy4;
	Slime* m_enemy5;
	Slime* m_enemy6;
	Slime* m_enemy7;
	
	PlayerHealthBar* m_healthBar;
	SpaceShip* m_player;

};

