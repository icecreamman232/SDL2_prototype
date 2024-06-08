#pragma once
#include <SDL.h>
#include "SDL_mixer.h"

#include <stdio.h>
#include <iostream>

#include "AssetManager.h"
#include "QuadTreev2.h"
#include "Scene.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "GameStateManager.h"

using namespace std;

class BMTextRenderer;


class Game
{
public:
	void Init(const char* title, int x, int y, int width, int height);
	void HandleEvents();
	void Update(float deltaTime);
	void Render(float deltaTime);
	void RenderImGUI();
	void Clean();
	inline void PassFPSValue(float value) { m_fps = value; };

	bool IsRunning();

	//static int ScreenWidth;
	//static int ScreenHeight;
	static SDL_Renderer* Renderer;
	static Scene* CurrentScene;
	static QuadTreev2* m_quadTreev2;
	static float DeltaTime;

private:
	bool m_isRunning;
	SDL_Window* m_window;

	Mix_Music* music;

	GameStateManager m_gameStateManager;

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

