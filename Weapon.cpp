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
	//m_pool = new ObjectPooler<Bullet>(number);
	m_generalName = generalName;
	m_texture = texture;
	m_width = width;
	m_height = height;
}


void Weapon::Shoot()
{
	if (m_isDelay) return;
	m_isDelay = true;

	//TODO:Implement scene system first before coming back here to continue with pooling
	//Bullet* bullet = m_pool->GetObject();
	//bullet->Initialize("Bullet",m_texture, 0, 0, m_width, m_height);
	

	Timer* delayTimer = new Timer(m_delayBetween2Shot, std::bind(&Weapon::AfterDelay, this));
}

void Weapon::AfterDelay()
{
	m_isDelay = false;
}



