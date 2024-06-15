#include "Weapon.h"
#include "Timer.h"
#include <iostream>
#include "Bullet.h"
#include "Game.h"

Weapon::Weapon(float delay)
{
	m_delayBetween2Shot = delay;
	m_isDelay = false;
	m_pool = nullptr;
	m_width = 0;
	m_height = 0;
}


void Weapon::InitializeBullet(int number, std::string generalName, SDL_Texture* texture, int width, int height)
{
	m_pool = new ObjectPooler<Bullet>(number);
	m_generalName = generalName;
	m_width = width;
	m_height = height;
}


void Weapon::Shoot(Vector2 pos,Vector2 direction, float angle)
{
	if (m_isDelay) return;
	m_isDelay = true;

	Bullet* bullet = m_pool->GetObject();
	bullet->Initialize(this,"Bullet",PLAYER_NORMAL_BULLET, pos.x, pos.y, m_width, m_height);
	bullet->SetDirection(direction);
	bullet->SetAngle(angle);

	Timer* delayTimer = new Timer(m_delayBetween2Shot, std::bind(&Weapon::AfterDelay, this));
}

void Weapon::Update(float deltaTime)
{
	if (!m_pool->m_activeList.empty())
	{
		for (Bullet* bullet : m_pool->m_activeList)
		{
			bullet->Update(deltaTime);
		}
	}
}

void Weapon::AfterDelay()
{
	m_isDelay = false;
}

void Weapon::ReleaseFromActivePool(Bullet* bullet)
{
	m_pool->ReleaseObject(bullet);
}

void Weapon::CleanUp()
{
	m_isDelay = true; //Dirty trick to stop weapon shooting
	Game::CurrentScene->RemoveAll(Render::RenderLayer::WEAPON);
	for (auto bullet : m_pool->m_activeList)
	{
		dynamic_cast<Bullet*>(bullet)->Remove();
	}
}

std::vector<Bullet*> Weapon::GetBulletList()
{
	return m_pool->m_activeList;
}



