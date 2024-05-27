#include "EnemySpawner.h"
#include "Game.h"
#include "Slime.h"
#include "string"
#include "Global.h"

using namespace General;

void EnemySpawner::Initialize()
{
	m_initDelayTime = 1.0f;
	m_delayTime = m_initDelayTime;
	m_timer = 0.0f;

	//Every 5 seconds, we reduce the delay time to spawn new enemy
	m_timeMark = 5.0;
	//The reduce value per 5 seconds
	m_delayTimeReduce = 0.1f;

	m_minDelayTime = 0.5f;

	m_numberSpawned = 0;
}

void EnemySpawner::Update(float deltaTime)
{
	UpdateTimer(deltaTime);

	UpdateEnemy(deltaTime);
}

void EnemySpawner::UpdateTimer(float deltaTime)
{
	m_timer += deltaTime;
	m_timerReduce += deltaTime;

	if (m_timerReduce >= m_timeMark)
	{
		m_timerReduce = 0;
		m_delayTime -= m_delayTimeReduce;
		if (m_delayTime <= m_minDelayTime)
		{
			m_delayTime = m_minDelayTime;
		}
	}

	if (m_timer >= m_delayTime)
	{
		SpawnNextEnemy();
		m_timer = 0;
	}
}

void EnemySpawner::UpdateEnemy(float deltaTime)
{
	for (auto enemy : m_spawnList)
	{
		if (!enemy.second->IsActive())
		{
			m_deadKeyList.push_back(enemy.first);
		}
		else 
		{
			enemy.second->Update(deltaTime);
			Game::m_quadTreev2->Insert(enemy.second);
		}
	}
	for (auto index : m_deadKeyList)
	{
		m_spawnList.erase(index);
	}
	m_deadKeyList.clear();
}

void EnemySpawner::SpawnNextEnemy()
{
	auto name = std::to_string(m_numberSpawned);

	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> distributionX(0, Game::ScreenWidth);
	std::uniform_int_distribution<int> distributionY(0, Game::ScreenHeight);

	auto x = distributionX(rng);
	auto y = distributionY(rng);

	auto newEnemy = new Slime(name.c_str(), TEXTURE_ID::SLIME_TEX, x, y, 16, 16, m_numberSpawned + 100);
	newEnemy->SetLayer(Layer::ENEMY);
	m_spawnList[m_numberSpawned] = newEnemy;
	Game::CurrentScene->Add(newEnemy,Render::RenderLayer::ENEMY);
	Game::m_quadTreev2->Insert(newEnemy);

	m_numberSpawned++;
}
