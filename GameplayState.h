#pragma once
#include "GameState.h"
#include "SpaceShip.h"
#include "EnemySpawner.h"
#include "BMTextRenderer.h"

class GameStateManager;

class GameplayState : public GameState
{
public:
	void Initialize(GameStateManager* manager) override;
	void Update(float deltaTime) override;
	void Render() override;

	inline SpaceShip* GetPlayer() { return m_player; };
private:

	std::string GetFormatedTime();

	GameStateManager* m_manager;

	SpaceShip* m_player;
	EnemySpawner* m_enemySpawner;

	int m_minute;
	int m_seconds;

	float m_secondsCounter;

	BMTextRenderer* m_waveTitle;
	BMTextRenderer* m_waveTimerText;
};

