#pragma once
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "Input.h"
#include "SpaceShip.h"
#include "QuadTree.h"
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

	QuadTree* m_quadTree;
	std::vector<GameObject*> m_collisionList;


	GameObject* m_enemy;
	GameObject* m_enemy1;
	GameObject* m_enemy2;
	GameObject* m_enemy3;
	GameObject* m_enemy4;
	GameObject* m_enemy5;

	SpaceShip* m_player;

};

