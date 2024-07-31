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
	public ISubscriber<CoinCollectEvent>,
	public ISubscriber<PlayerStateEvent>
{
public:
	void Initialize(GameStateManager* manager) override;
	void Update(float deltaTime) override;
	void Render() override;
	void ExitState() override;

	void OnTriggerEvent(const LevelUpEvent& eventType) override;
	void OnTriggerEvent(const EnemyHealthEvent& eventType) override;
	void OnTriggerEvent(const CoinCollectEvent& eventType) override;
	void OnTriggerEvent(const PlayerStateEvent& eventType) override;

	inline SpaceShip* GetPlayer() { return m_player; };
private:
	enum GameplayInternalState
	{
		PREV_STATE = 0,
		MAIN_STATE = 1,
		END_WAVE = 2,
		GAME_OVER = 3,
	};


	void InitializeUI();
	std::string GetFormatedTime();

	void UpdateUI();
	void UpdateMainState(float deltaTime);
	void OnFinishShowLevelUpText();
	void OnFinishPrevStateTween();
	void OnAfterShowHUD();

	GameplayInternalState m_internalState;
	GameStateManager* m_manager;
	SpaceShip* m_player;
	EnemySpawner m_enemySpawner;

	int m_coinAmount;
	int m_numEnemyKilled; //Testing

	//===== WAVE====//
	Uint8 m_minute;
	Uint8 m_seconds;
	float m_secondsCounter;

	//===== UI =====//
	std::string m_hpTxtValue;
	std::string m_levelTxtValue;

	PlayerUIBar* m_healthBar;
	PlayerUIBar* m_expBar;

	BMTextRenderer m_coinText;
	BMTextRenderer m_hpText;
	BMTextRenderer m_levelText;
	BMTextRenderer m_waveTitle;
	BMTextRenderer m_waveTimerText;
	BMTextRenderer m_levelUpText;

	UIImage* m_coinIcon;
	UIImage* m_fullScreenFadeBG;

	//====Drops===//
	DropsManager* m_moneyDropsMnger;

	//===CONSTANT===//
	const float m_prevStateTweenDuration = 1.5f;
	const float m_hudFadeInDuration = 0.3f;
	const int m_firstWaveDuration = 50;
};

