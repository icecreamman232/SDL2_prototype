#pragma once
#include "GameplayState.h"

class GameStateManager
{
public:
	void Initialize();
	void Update(float deltaTime);
	void Render();
	inline GameState* CurrentState() { return m_currentState; };
	inline int GetCurrentWaveIndex() { return m_waveIndex; };
private:
	GameState* m_currentState;
	int m_waveIndex;
};

