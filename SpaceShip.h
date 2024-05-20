#pragma once
#include "GameObject.h"
class SpaceShip : public GameObject
{
public:
	SpaceShip(const char* name,SDL_Texture* texturePath, int initX, int initY,int width, int height);
	void Update(float deltaTime) override;

	void SetDirectionX(float);
	void SetDirectionY(float);

private:
	float m_moveSpeed;
	Vector2 m_direction;
};

