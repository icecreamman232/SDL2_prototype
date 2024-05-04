#include "Input.h"

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