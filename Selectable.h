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
	virtual void OnSelect() {};
	virtual void OnDeselect() {};
	inline bool IsMouseEnter() { return m_isEnter; };
	inline bool IsSelected() { return m_isSelected; };
	void SetInteract(bool canInteract);
protected:
	SDL_FRect m_rect;
	bool m_canInteract = true;
	bool m_isSelected = false;
	bool m_isEnter = false;
};

