#include "DropsManager.h"
#include <random>
#include "Game.h"
#include "CoinCollectEventDispatcher.h"

DropsManager::DropsManager(int initialAmount)
{
	m_pool = new ObjectPooler<IItem>(initialAmount);
	m_collectCoinSFX = Mix_LoadWAV("Asset/Sound/coin-collect.wav");
	Mix_VolumeChunk(m_collectCoinSFX, MIX_MAX_VOLUME / 2);
}

void DropsManager::Drop(int amount, Vector2 spawnPos)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(-1.0, 1.0);
	for (int i=0;i < amount;i++)
	{
		auto x = dist(gen)*50 + spawnPos.x;
		auto y = dist(gen)*50 + spawnPos.y;
		auto drop = m_pool->GetObject();
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

			CoinCollectEventDispatcher::Trigger(CoinCollectEvent{ 1 });
			Mix_PlayChannel(-1, m_collectCoinSFX,0);
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

void DropsManager::Cleanup()
{
	for (auto drop : m_pool->m_activeList)
	{
		Game::CurrentScene->Remove(dynamic_cast<GameObject*>(drop), Render::RenderLayer::ITEM);
	}
}
