#pragma once
#include "ObjectPooler.h"
#include "Bullet.h"

class Weapon
{
public:
	Weapon(float delay);
	void InitializeBullet(int number, std::string generalName, SDL_Texture* texture, int width, int height);
	void Shoot();

private:
	bool m_isDelay;
	float m_delayBetween2Shot;
	ObjectPooler<Bullet>* m_pool;


	std::string m_generalName;
	SDL_Texture* m_texture;
	int m_width;
	int m_height;

	void AfterDelay();
};

