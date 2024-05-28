#pragma once
#include "GameState.h"
#include "SpaceShip.h"
#include "EnemySpawner.h"
#include "BMTextRenderer.h"
#include "PlayerHealthBar.h"
#include "EnemyHealthEventDispatcher.h"

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

	//===== WAVE====//
	int m_minute;
	int m_seconds;
	float m_secondsCounter;

	//===== UI =====//
	PlayerHealthBar* m_healthBar;
	BMTextRenderer* m_waveTitle;
	BMTextRenderer* m_waveTimerText;

	//===Events===//
	EnemyHealthEventDispatcher m_enemyHealthEventDispatcher;
};

