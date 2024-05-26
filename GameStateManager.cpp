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

	m_currentState->Update(deltaTime);
}

void GameStateManager::Render()
{
	m_currentState->Render();
}
