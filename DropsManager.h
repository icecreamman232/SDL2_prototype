#pragma once
#include "SDL_mixer.h"
#include "ObjectPooler.h"
#include "IItem.h"

class DropsManager
{
public:
	DropsManager(int initialAmount);
	void Drop(int amount, Vector2 spawnPos);
	void Update(GameObject* objectToCheck, float deltaTime);
private:
	ObjectPooler<IItem>* m_pool;
	std::vector<IItem*> m_toBeRemovedList;

	Mix_Chunk* m_collectCoinSFX;
};

