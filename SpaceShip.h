#pragma once
#include "GameObject.h"
class SpaceShip : public GameObject
{
public:
	SpaceShip(const char* name,const char* texturePath, SDL_Renderer* renderer, int initX, int initY,int width, int height);
	void Update(float deltaTime) override;

	void SetDirectionX(float);
	void SetDirectionY(float);

private:
	float m_moveSpeed;
	Vector2 m_direction;
	const double LIMIT_LEFT = 0;
	const double LIMIT_RIGHT = 1368;
	const double LIMIT_UP = 0;
	const double LIMIT_DOWN = 768;
};

