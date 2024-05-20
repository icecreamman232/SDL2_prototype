#pragma once
#include <SDL.h>
#include "AssetManager.h"
#include "Math/Vector2.h"
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(int id, const char* name, SDL_Texture* texture,
		int initX, int initY, int width, int height);
	void Update(float deltaTime) override;
	void Render();
	void SetAngle(float angle);
private:

	float m_moveSpeed;
	Vector2 m_direction;
};

