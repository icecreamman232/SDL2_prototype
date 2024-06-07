#pragma once
#include "GameState.h"
#include "SpaceShip.h"
#include "EnemySpawner.h"
#include "BMTextRenderer.h"
#include "UIImage.h"
#include "PlayerUIBar.h"
#include "ISubscriber.h"
#include "DropsManager.h"

class GameStateManager;

class GameplayState : public GameState,
	public ISubscriber<LevelUpEvent>,
	public ISubscriber<EnemyHealthEvent>,
	public ISubscriber<CoinCollectEvent>
{
public:
	void Initialize(GameStateManager* manager) override;
	void Update(float deltaTime) override;
	void Render() override;
	void ExitState() override;

	void OnTriggerEvent(const LevelUpEvent& eventType) override;
	void OnTriggerEvent(const EnemyHealthEvent& eventType) override;
	void OnTriggerEvent(const CoinCollectEvent& eventType) override;

	inline SpaceShip* GetPlayer() { return m_player; };
private:

	void InitializeUI();
	std::string GetFormatedTime();
	void UpdateUI();

	GameStateManager* m_manager;
	SpaceShip* m_player;
	EnemySpawner* m_enemySpawner;

	Uint16 m_numLvGained;

	int m_coinAmount;


	//===== WAVE====//
	int m_minute;
	int m_seconds;
	float m_secondsCounter;

	//===== UI =====//
	std::string m_hpTxtValue;
	std::string m_levelTxtValue;

	PlayerUIBar* m_healthBar;
	PlayerUIBar* m_expBar;

	BMTextRenderer* m_coinText;
	BMTextRenderer* m_hpText;
	BMTextRenderer* m_levelText;
	BMTextRenderer* m_waveTitle;
	BMTextRenderer* m_waveTimerText;

	UIImage* m_coinIcon;
	UIImage* m_lvlUpIcon;

	//====Drops===//
	DropsManager* m_moneyDropsMnger;

};

