#include "Collider.h"

Collider::Collider(GameObject* owner)
{
	m_owner = owner;
}

bool Collider::IsCollideWith(GameObject* other)
{
	if (m_owner == nullptr)
	{
		return false;
	}

	if (AABBCheck(m_owner->Rect(), other->Rect()))
	{
		return true;
	}
	

	return false;
}

bool Collider::AABBCheck(const SDL_FRect& rect1, const SDL_FRect& rect2)
{
	if (rect1.x + rect1.w >= rect2.x &&
		rect2.x + rect2.w >= rect1.x &&
		rect1.y + rect1.h >= rect2.y &&
		rect2.y + rect2.h >= rect1.y) {
		// Collision detected
		return true;
	}

	return false;
}

