#include "Global.h"
#include "GameplayState.h"
#include "Game.h"
#include <iostream>
#include "GameStateManager.h"
#include <string>
#include <sstream>
#include "Slime.h"
#include "PlayerLevelUpEventDispatcher.h"
#include "EnemyHealthEventDispatcher.h"
#include "CoinCollectEventDispatcher.h"
#include "TweenManager.h"

void GameplayState::Initialize(GameStateManager* manager)
{
	m_manager = manager;


	m_minute = 0;
	m_seconds = 6;
	m_secondsCounter = 0.0;
	m_numLvGained = 0;

	m_player = new SpaceShip("Ship", PLAYER_TEX, g_WindowSettings.Width / 2, g_WindowSettings.Height / 2, 18, 16, 9);
	m_player->SetLayer(Layer::PLAYER);


	Game::m_quadTreev2->Insert(m_player);

	m_enemySpawner.Initialize();


	InitializeUI();


	Game::CurrentScene->Add(m_waveTitle);
	Game::CurrentScene->Add(m_waveTimerText);
	Game::CurrentScene->Add(m_healthBar);
	Game::CurrentScene->Add(m_expBar);
	Game::CurrentScene->Add(m_hpText);
	Game::CurrentScene->Add(m_levelText);
	Game::CurrentScene->Add(m_coinIcon);
	Game::CurrentScene->Add(m_coinText);
	Game::CurrentScene->Add(m_lvlUpIcon);

	m_healthBar->FadeIn(0.5f);
	m_expBar->FadeIn(0.5f);


	m_moneyDropsMnger = new DropsManager(20);

	EnemyHealthEventDispatcher::Attach(this);
	PlayerLevelUpEventDispatcher::Attach(this);
	CoinCollectEventDistpacher::Attach(this);

	m_isRunning = true;
}

void GameplayState::Update(float deltaTime)
{
	if (!m_isRunning) return;
	m_secondsCounter += deltaTime;
	if (m_secondsCounter >= 1.0)
	{
		m_secondsCounter = 0;
		m_seconds--;
		if (m_seconds <= 0)
		{
			m_seconds = 0;
			m_minute--;
			if (m_minute <= 0)
			{
				m_minute = 0;
				m_waveTimerText->SetText(GetFormatedTime());

				//Time is over and we stop gameplay 
				// and ready to start end wave screen
				ExitState();
				return;
			}
		}
		m_waveTimerText->SetText(GetFormatedTime());
	}

	
	m_enemySpawner.Update(deltaTime);

	m_player->Update(deltaTime);
	Game::m_quadTreev2->Insert(m_player);
	
	
	//Check collision between player and enemy
	auto result = Game::m_quadTreev2->GetCollision(m_player, Layer::ENEMY);
	if (result != nullptr)
	{
		auto slime = dynamic_cast<Slime*>(result);
		if (slime != nullptr)
		{
			m_player->TakeDamage(slime->GetDamage());
		}
	}
	//Check collision between player and coins
	m_moneyDropsMnger->Update(m_player, deltaTime);


	UpdateUI();
}

void GameplayState::Render()
{
	
}

void GameplayState::ExitState()
{
	//Detach all events
	EnemyHealthEventDispatcher::Detach(this);
	PlayerLevelUpEventDispatcher::Detach(this);
	CoinCollectEventDistpacher::Detach(this);

	m_isRunning = false;

	m_enemySpawner.StopAndClear();
	m_player->SetActive(false);

	delete m_player;

	m_manager->BeginChangeState();
	m_manager->ChangeState(General::GameStateType::ENDWAVE);
	m_manager->EndChangeState();
}

void GameplayState::OnTriggerEvent(const LevelUpEvent& eventType)
{
	m_levelTxtValue = "Lv " + std::to_string(m_player->XPController().GetCurrentLv());
	m_numLvGained++;
}

void GameplayState::OnTriggerEvent(const EnemyHealthEvent& eventType)
{
	if (eventType.IsDead)
	{
		//Drop items at enemy dead spot
		m_moneyDropsMnger->Drop(3, eventType.DeadPosition);
	}
}

void GameplayState::OnTriggerEvent(const CoinCollectEvent& eventType)
{
	m_coinAmount++;
}

void GameplayState::InitializeUI()
{
	//Health bar
	m_healthBar = new PlayerUIBar(20, 20, 200, 20);
	m_healthBar->SetBarColor({ 255, 0, 0 });
	m_healthBar->SetBackgroundColor({ 255, 155, 155 });

	//Health text inside health bar
	m_hpTxtValue = std::to_string(m_player->GetHealth().GetCurrentHealth())
		+ "/"
		+ std::to_string(m_player->GetHealth().GetMaxHealth());
	m_hpText = new BMTextRenderer(TEXTURE_ID::BM_FONT_PIXEL, m_hpTxtValue, Render::Pivot::CENTER, 115, 22);
	m_hpText->SetSpacing(8);
	m_hpText->SetSize(16);

	//Exp bar
	m_expBar = new PlayerUIBar(20, 50, 200, 20);
	m_expBar->SetBarColor({ 0,162,232 });
	m_expBar->SetBackgroundColor({ 142, 214, 232 });
	m_expBar->SetBarFillInstant(0);

	//Exp text inside exp bar
	m_levelTxtValue = "Lv " + std::to_string(m_player->XPController().GetCurrentLv());
	m_levelText = new BMTextRenderer(TEXTURE_ID::BM_FONT_PIXEL, m_levelTxtValue, Render::Pivot::CENTER, 120, 52);
	m_levelText->SetSpacing(8);
	m_levelText->SetSize(16);

	//Wave title text
	auto title = "WAVE " + std::to_string(m_manager->GetCurrentWaveIndex());
	m_waveTitle = new BMTextRenderer(TEXTURE_ID::BM_FONT_PIXEL, title, Render::Pivot::CENTER, g_WindowSettings.Width / 2.0f, 10);
	m_waveTitle->SetSpacing(20);
	m_waveTitle->SetSize(32);

	//Wave timer text
	m_waveTimerText = new BMTextRenderer(TEXTURE_ID::BM_FONT_PIXEL, GetFormatedTime(), Render::Pivot::CENTER, g_WindowSettings.Width / 2.0f + 15, 50);
	m_waveTimerText->SetSpacing(16);
	m_waveTimerText->SetSize(24);

	//Coin icon
	m_coinIcon = new UIImage();
	m_coinIcon->Init(Render::TEXTURE_ID::COIN, 15, 70, 20, 20);

	//Number coin text
	m_coinText = new BMTextRenderer(TEXTURE_ID::BM_FONT_PIXEL, std::to_string(m_coinAmount), Render::Pivot::CENTER, 70, 90);
	m_coinText->SetSpacing(14);
	m_coinText->SetSize(24);

	m_lvlUpIcon = new UIImage();
	m_lvlUpIcon->Init(Render::TEXTURE_ID::LVL_UP_ICON, g_WindowSettings.Width - 100, 30, 24, 24);


	TweenManager::Instance().CreateTween(Tween::TweenEase::IN_OUT_BOUNCE,
		m_lvlUpIcon, g_WindowSettings.Width - 100, 200, 2);
	
}

std::string GameplayState::GetFormatedTime()
{
	//Update timer text
	std::stringstream ss;

	if (m_minute < 10)
	{
		ss << '0';
		ss << m_minute;
	}
	else
	{
		ss << m_minute;
	}
	ss << ":";

	if (m_seconds < 10)
	{
		ss << '0';
		ss << m_seconds;
	}
	else
	{
		ss << m_seconds;
	}


	std::string formattedTimer = ss.str();

	return formattedTimer;
}

void GameplayState::UpdateUI()
{
	m_healthBar->UpdateBar(m_player->GetPercentHealth());

	m_hpTxtValue = std::to_string(m_player->GetHealth().GetCurrentHealth())
		+ "/"
		+ std::to_string(m_player->GetHealth().GetMaxHealth());
	m_hpText->SetText(m_hpTxtValue);

	m_expBar->UpdateBar(m_player->XPController().GetXPPercent());

	m_levelText->SetText(m_levelTxtValue);

	m_coinIcon->Update();
	m_coinText->SetText(std::to_string(m_coinAmount));

	m_lvlUpIcon->Update();
}


