#pragma once
#include <map>
#include "GameObject.h"
#include "random"

class EnemySpawner
{
public:
	void Initialize();
	void Update(float deltaTime);
	void Stop();
	void StopAndClear();
private:
	void UpdateTimer(float deltaTime);
	void UpdateEnemy(float deltaTime);
	void SpawnNextEnemy();

	bool m_shouldUpdate = false;

	float m_timer;
	float m_initDelayTime;
	float m_delayTime;
	int m_numberSpawned;

	//After this time duration, spawn delay time will be reduced to increase tension
	float m_timerReduce;
	float m_timeMark;
	float m_delayTimeReduce;
	float m_minDelayTime;
	

	std::random_device rd;

	std::vector<int> m_deadKeyList;
	std::map<int, GameObject*> m_spawnList;
};

