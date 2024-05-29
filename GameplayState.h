#pragma once
#include "GameState.h"
#include "SpaceShip.h"
#include "EnemySpawner.h"
#include "BMTextRenderer.h"
#include "PlayerUIBar.h"
#include "ISubscriber.h"
#include "EnemyHealthEventDispatcher.h"

class GameStateManager;

class GameplayState : public GameState,
	public ISubscriber<LevelUpEvent>
{
public:
	void Initialize(GameStateManager* manager) override;
	void Update(float deltaTime) override;
	void Render() override;

	void OnTriggerEvent(const LevelUpEvent& eventType) override;

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
	PlayerUIBar* m_healthBar;
	PlayerUIBar* m_expBar;
	BMTextRenderer* m_waveTitle;
	BMTextRenderer* m_waveTimerText;

};

