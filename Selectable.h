#pragma once
#include "SDL_rect.h"

class Selectable
{
public:
	virtual void InitSelectable(float x, float y, float width, float height);
	virtual void UpdateSelectable();

	virtual void OnMouseEnter() {};
	virtual void OnMouseExit() {};
	virtual void OnMouseLeftClick() {};
	inline bool IsMouseEnter() { return m_isEnter; };
	void SetInteract(bool canInteract);
protected:
	SDL_FRect m_rect;
	bool m_canInteract = true;
	bool m_isEnter = false;
};

