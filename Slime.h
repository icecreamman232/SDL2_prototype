#pragma once
#include "GameObject.h"
#include <random>

class Slime : public GameObject
{
public:
	Slime(int id,const char* name, const char* texturePath, SDL_Renderer* renderer,
		int initX, int initY, int width, int height);

	void Update(float deltaTime) override;
private:

	void GetNextDirection(Vector2& direction);

	std::mt19937 randomGenerator;

	int m_id;
	float m_moveSpeed;
	Vector2 m_direction;
};

