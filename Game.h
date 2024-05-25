#pragma once
#include <SDL.h>
#include "SDL_mixer.h"

#include <stdio.h>
#include <iostream>

#include "AssetManager.h"
#include "SpaceShip.h"
#include "Slime.h"
#include "QuadTreev2.h"
#include "PlayerHealthBar.h"
#include "Scene.h"


#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

using namespace std;

class BMTextRenderer;

class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int x, int y, int width, int height);
	void HandleEvents();
	void Update(float deltaTime);
	void Render(float deltaTime);
	void RenderImGUI();
	void Clean();
	inline void PassFPSValue(float value) { m_fps = value; };

	bool IsRunning();

	static int ScreenWidth;
	static int ScreenHeight;
	static SDL_Renderer* Renderer;
	static Scene* CurrentScene;
	static QuadTreev2* m_quadTreev2;

private:
	bool m_isRunning;
	SDL_Window* m_window;

	std::vector<GameObject*> m_collisionList;

	Mix_Music* music;

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


	BMTextRenderer* m_text;

	//ImGUI
	ImGuiIO io;
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	//FPS overlay
	float m_fps;
	const float PAD = 10.0f;
	const ImGuiViewport* m_viewport;
	bool m_showFPSOverlay = false;
	ImGuiWindowFlags m_FPSOverlayWindownFlags;
};

