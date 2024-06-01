#include "DropsManager.h"
#include <random>
#include <iostream>
#include "Game.h"

DropsManager::DropsManager(int initialAmount)
{
	m_pool = new ObjectPooler<IItem>(initialAmount);
}

void DropsManager::Drop(int amount, Vector2 spawnPos)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(-1.0, 1.0);
	std::cout << "====Spawn item====\n";
	for (int i=0;i < amount;i++)
	{
		auto x = dist(gen)*50 + spawnPos.x;
		auto y = dist(gen)*50 + spawnPos.y;
		auto drop = m_pool->GetObject();
		std::cout << "Spawn at x " << x << " y " << y << "\n";
		drop->Initialize("Drops", Render::TEXTURE_ID::COIN, x, y, 16, 16);
		
		Game::CurrentScene->Add(dynamic_cast<GameObject*>(drop),Render::RenderLayer::ITEM);
	}
}

void DropsManager::Update(GameObject* objectToCheck, float deltaTime)
{
	for (int i = 0; i < m_pool->m_activeList.size(); i++)
	{
		m_pool->m_activeList[i]->Update(deltaTime);

		if (objectToCheck->IsCollideWith(m_pool->m_activeList[i]))
		{
			m_toBeRemovedList.push_back(m_pool->m_activeList[i]);
			m_pool->m_activeList[i]->SetCollide(false);
			Game::CurrentScene->Remove(m_pool->m_activeList[i], Render::RenderLayer::ITEM);
		}
	}

	if (!m_toBeRemovedList.empty())
	{
		for (auto item : m_toBeRemovedList)
		{
			m_pool->ReleaseObject(item);
		}
		m_toBeRemovedList.clear();
	}
}
