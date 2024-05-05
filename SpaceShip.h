#pragma once
#include "GameObject.h"
class SpaceShip : public GameObject
{
public:
	SpaceShip(const char* texturePath, SDL_Renderer* renderer, int initX, int initY);
	void Update(float deltaTime) override;

	void SetDirectionX(float);
	void SetDirectionY(float);

private:
	float m_moveSpeed;
	float m_directionX;
	float m_directionY;
	const double LIMIT_LEFT = 0;
	const double LIMIT_RIGHT = 1368;
	const double LIMIT_UP = 0;
	const double LIMIT_DOWN = 768;
};

