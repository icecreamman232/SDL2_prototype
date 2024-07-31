#include "GameStateManager.h"

void GameStateManager::Initialize()
{
	m_waveIndex = 1; //Start at wave 1, absolutely!
	m_powerUpManager.Initialize();

	m_currentState = new GameOverState();
	m_currentState->Initialize(this);

}

void GameStateManager::Update(float deltaTime)
{
	if (m_isChangingState) return;

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

	GameState* newState = nullptr;

	switch (nextState)
	{
		case GameStateType::GAMEPLAY:
			m_waveIndex = 1;
			newState = new GameplayState();
			break;
		case GameStateType::ENDWAVE:
			newState = new EndWaveState();
			break;
		case GameStateType::GAMEOVER:
			newState = new GameOverState();
			break;
	}

	if (newState)
	{
		newState->Initialize(this);
		delete m_currentState;
		m_isChangingState = false;
		m_currentState = newState;
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
