#pragma once
#include "GameObject.h"
#include <random>

class Slime : public GameObject
{
public:
	Slime(int id,const char* name, TEXTURE_ID textureID ,
		int initX, int initY, int width, int height,int order = 0);

	void Update(float deltaTime) override;

private:

	void GetNextDirection(Vector2& direction);

	std::mt19937 randomGenerator;

	int m_id;
	float m_moveSpeed;
	Vector2 m_direction;
};

