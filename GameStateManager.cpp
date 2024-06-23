#include "GameStateManager.h"

void GameStateManager::Initialize()
{
	m_waveIndex = 1; //Start at wave 1, absolutely!

	m_currentState = new GameplayState();
	m_currentState->Initialize(this);

}

void GameStateManager::Update(float deltaTime)
{
	if (m_currentState == nullptr) return;

	if (!m_currentState->IsRunning()) return;

	m_currentState->Update(deltaTime);
}

void GameStateManager::Render()
{
	m_currentState->Render();
}

void GameStateManager::BeginChangeState()
{
	m_isChangingState = true;
}

void GameStateManager::ChangeState(GameStateType nextState)
{
	if (!m_isChangingState) return;

	switch (nextState)
	{
		case GameStateType::ENDWAVE:
			delete m_currentState;
			m_currentState = new EndWaveState();
			m_currentState->Initialize(this);

			m_isChangingState = false;
			break;
	}
}

void GameStateManager::EndChangeState()
{
	m_isChangingState = false;
}

void GameStateManager::LevelGained()
{
	m_levelGainedDuringRun++;
}

PowerUpManager* GameStateManager::GetPowerUpManager()
{
	return &m_powerUpManager;
}
