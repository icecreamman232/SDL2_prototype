#pragma once
#include "ObjectPooler.h"

class Weapon
{
public:
	Weapon(float delay);
	void InitializeBullet(int number, std::string generalName, SDL_Texture* texture, int width, int height);
	void Shoot();

private:
	bool m_isDelay;
	float m_delayBetween2Shot;
	ObjectPooler* m_pool;


	void AfterDelay();
};

