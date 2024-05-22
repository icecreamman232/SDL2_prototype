#pragma once
#include "GameObject.h"
#include <random>
#include "Health.h"

class Slime : public GameObject
{
public:
	Slime(const char* name, TEXTURE_ID textureID ,
		int initX, int initY, int width, int height,int order = 0);

	void Update(float deltaTime) override;
	void TakeDamage(int damage);
private:

	void GetNextDirection(Vector2& direction);

	std::mt19937 randomGenerator;

	float m_moveSpeed;
	Vector2 m_direction;
	Health* m_health;
};

