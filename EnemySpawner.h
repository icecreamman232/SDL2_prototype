#pragma once
#include <map>
#include "GameObject.h"
#include "random"

class EnemySpawner
{
public:
	void Initialize();
	void Update(float deltaTime);
private:
	void UpdateTimer(float deltaTime);
	void UpdateEnemy(float deltaTime);
	void SpawnNextEnemy();

	float m_timer;
	float m_delayTime;
	int m_numberSpawned;

	std::random_device rd;

	std::vector<int> m_deadKeyList;
	std::map<int, GameObject*> m_spawnList;
};

