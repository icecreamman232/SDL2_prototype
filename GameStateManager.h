#pragma once
#include "GameplayState.h"
#include "Global.h"

class GameStateManager
{
public:
	void Initialize();
	void Update(float deltaTime);
	void Render();
	void BeginChangeState();
	void ChangeState(GameStateType nextState);
	void EndChangeState();
	inline GameState* CurrentState() { return m_currentState; };
	inline int GetCurrentWaveIndex() { return m_waveIndex; };
	inline bool IsChangingState() { return m_isChangingState; };
private:
	GameState* m_currentState;
	int m_waveIndex;
	bool m_isChangingState;
};

