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

	//Handle mouse hover
	if (m_isEnter)
	{
		if (!(x < m_rect.x + m_rect.w && x > m_rect.x)
			|| !(y < m_rect.y + m_rect.h && y > m_rect.y))
		{
			OnMouseExit();
			m_isEnter = false;
		}
	}
	else 
	{
		if ((x < m_rect.x + m_rect.w && x > m_rect.x)
			&& (y < m_rect.y + m_rect.h && y > m_rect.y))
		{
			OnMouseEnter();
			m_isEnter = true;
		}
	}

	//Handle selection
	if (m_isEnter)
	{
		if (Input::Instance().IsLeftMouseDown())
		{
			OnMouseLeftClick();
			if (!m_isSelected)
			{
				OnSelect();
				m_isSelected = true;
			}
		}
	}
	else 
	{
		if (Input::Instance().IsLeftMouseDown())
		{
			if (m_isSelected)
			{
				OnDeselect();
				m_isSelected = false;
			}
		}
	}
}

void Selectable::SetInteract(bool canInteract)
{
	m_canInteract = canInteract;
}
