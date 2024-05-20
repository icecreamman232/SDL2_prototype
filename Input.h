#pragma once
#include <SDL.h>
#include "Singleton.h"

class Input : public Singleton<Input>
{
public:
	void Initialize();
	void HandleEvent(SDL_Event* event);

	int MouseX;
	int MouseY;
	
	bool IsLeftMouseDown();
	bool GetKeyDown(SDL_Scancode keyCode);

private:
	//std::<map>
	const Uint8* m_keyStates;
	bool m_isLeftMouseDown;
};

enum KeyState
{
	RELEASE,
	PRESS,
};

struct KeyCodeState
{
	KeyState State;
	SDL_Scancode KeyCode;
};

