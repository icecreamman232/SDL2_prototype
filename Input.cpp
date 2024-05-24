#include "Input.h"

void Input::Initialize()
{
	//m_keyStates = SDL_GetKeyboardState(NULL);
}

void Input::HandleEvent(SDL_Event* event)
{
	m_prevKeyStates = m_keyStates;
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
		case SDL_QUIT:
			break;
		case SDL_KEYDOWN:
			m_keyStates[event->key.keysym.scancode] = true;
			break;
		case SDL_KEYUP:
			m_keyStates[event->key.keysym.scancode] = false;
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

bool Input::GetKeyPressed(SDL_Scancode keyCode)
{
	return GetKeyDown(keyCode) && !m_prevKeyStates[keyCode];
}
