#include "Selectable.h"
#include "Input.h"

void Selectable::InitSelectable(float x, float y, float width, float height)
{
	m_rect.x = x;
	m_rect.y = y;
	m_rect.w = width;
	m_rect.h = height;
 }

void Selectable::UpdateSelectable()
{
	if (!m_canInteract) return;

	int x = Input::Instance().MouseX;
	int y = Input::Instance().MouseY;

	if((x < m_rect.x + m_rect.w && x > m_rect.x)
		&& (y < m_rect.y + m_rect.h && y > m_rect.y)
		&& !m_isEnter)
	{
		OnMouseEnter();
		m_isEnter = true;
	}
	else
	{
		if (m_isEnter)
		{
			OnMouseExit();
			m_isEnter = false;
		}
	}

	if (m_isEnter)
	{
		if (Input::Instance().IsLeftMouseDown())
		{
			OnMouseLeftClick();
		}
	}
}
