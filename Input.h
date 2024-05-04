#pragma once
#include <SDL.h>
class Input
{
public:
	void HandleEvent(SDL_Event* event);

	int MouseX;
	int MouseY;
	
	bool IsLeftMouseDown();
private:
	bool m_isLeftMouseDown;
};

