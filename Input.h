#pragma once
#include <SDL.h>
#include "Singleton.h"
#include <unordered_map>

class Input : public Singleton<Input>
{
public:
	void Initialize();
	void HandleEvent(SDL_Event* event);

	int MouseX;
	int MouseY;
	
	bool IsLeftMouseDown();
	bool GetKeyDown(SDL_Scancode keyCode);
	bool GetKeyPressed(SDL_Scancode keyCode);

private:
	std::unordered_map<SDL_Scancode, bool> m_keyStates;
	std::unordered_map<SDL_Scancode, bool> m_prevKeyStates;

	bool m_isLeftMouseDown;
};


