#include "Input.h"

void Input::Initialize()
{
	m_keyStates = SDL_GetKeyboardState(NULL);
}

void Input::HandleEvent(SDL_Event* event)
{
	switch (event->type)
	{
		case SDL_MOUSEBUTTONDOWN:
			if (event->button.button == SDL_BUTTON_LEFT)
			{
				m_isLeftMouseDown = true;
			}
			SDL_GetMouseState(&MouseX, &MouseY);
			break;
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&MouseX, &MouseY);
			break;
		case SDL_SCANCODE_DOWN:
			break;
		case SDL_QUIT:
			break;
		default:
			m_isLeftMouseDown = false;
			break;
	}
	
}

bool Input::IsLeftMouseDown()
{
	return m_isLeftMouseDown;
}

bool Input::GetKeyDown(SDL_Scancode keyCode)
{
	return m_keyStates[keyCode];
}
