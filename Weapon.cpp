#include "Weapon.h"
#include "Timer.h"
#include <iostream>
#include "Bullet.h"

Weapon::Weapon(float delay)
{
	m_delayBetween2Shot = delay;
	m_isDelay = false;
	m_pool = nullptr;
}

void Weapon::InitializeBullet(int number, std::string generalName, SDL_Texture* texture, int width, int height)
{
	m_pool = new ObjectPooler(number, generalName, texture, width, height);
}


void Weapon::Shoot()
{
	if (m_isDelay) return;
	m_isDelay = true;

	GameObject* object = m_pool->GetPooledGameObject();
	Bullet* bullet = dynamic_cast<Bullet*>(object);

	//TODO:Spawn bullet here

	Timer* delayTimer = new Timer(m_delayBetween2Shot, std::bind(&Weapon::AfterDelay, this));
}

void Weapon::AfterDelay()
{
	m_isDelay = false;
}



