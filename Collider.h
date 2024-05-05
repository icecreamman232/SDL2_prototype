#pragma once
#include "GameObject.h"

class Collider
{
public:
	Collider(GameObject* owner);
	bool IsCollideWith(GameObject* other);

private:
	GameObject* m_owner;
	bool AABBCheck(const SDL_FRect& rect1, const SDL_FRect& rect2);
};

