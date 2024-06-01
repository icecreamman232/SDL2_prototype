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

void GameplayState::Initialize(GameStateManager* manager)
{
	m_manager = manager;


	m_minute = 0;
	m_seconds = 30;
	m_secondsCounter = 0.0;


	m_player = new SpaceShip("Ship", PLAYER_TEX, Game::ScreenWidth / 2, Game::ScreenHeight / 2, 18, 16, 9);
	m_player->SetLayer(Layer::PLAYER);


	Game::m_quadTreev2->Insert(m_player);

	m_enemySpawner = new EnemySpawner();
	m_enemySpawner->Initialize();

	m_healthBar = new PlayerUIBar(20, 20, 200, 20);
	m_healthBar->SetBarColor({ 255, 0, 0 });
	m_healthBar->SetBackgroundColor({ 255, 155, 155 });

	m_hpTxtValue = std::to_string(m_player->GetHealth().GetCurrentHealth()) 
								+ "/" 
								+ std::to_string(m_player->GetHealth().GetMaxHealth());
	m_hpText = new BMTextRenderer(TEXTURE_ID::BM_FONT_PIXEL, m_hpTxtValue, Render::Pivot::CENTER, 115, 22);
	m_hpText->SetSpacing(8);
	m_hpText->SetSize(16);


	m_expBar = new PlayerUIBar(20, 50, 200, 20);
	m_expBar->SetBarColor({ 0,162,232 });
	m_expBar->SetBackgroundColor({ 142, 214, 232 });
	m_expBar->SetBarFillInstant(0);

	m_levelTxtValue = "Lv " + std::to_string(m_player->XPController().GetCurrentLv());

	m_levelText = new BMTextRenderer(TEXTURE_ID::BM_FONT_PIXEL, m_levelTxtValue, Render::Pivot::CENTER, 120, 52);
	m_levelText->SetSpacing(8);
	m_levelText->SetSize(16);

	auto title = "WAVE " + std::to_string(m_manager->GetCurrentWaveIndex());
	m_waveTitle = new BMTextRenderer(TEXTURE_ID::BM_FONT_PIXEL, title, Render::Pivot::CENTER, Game::ScreenWidth / 2, 10);
	m_waveTitle->SetSpacing(20);
	m_waveTitle->SetSize(32);

	m_waveTimerText = new BMTextRenderer(TEXTURE_ID::BM_FONT_PIXEL, GetFormatedTime(), Render::Pivot::CENTER, Game::ScreenWidth / 2 + 15, 50);
	m_waveTimerText->SetSpacing(16);
	m_waveTimerText->SetSize(24);

	m_coinIcon = new UIImage();
	m_coinIcon->Init(Render::TEXTURE_ID::COIN, 15, 70, 20, 20);

	m_coinText = new BMTextRenderer(TEXTURE_ID::BM_FONT_PIXEL, std::to_string(m_coinAmount), Render::Pivot::CENTER, 70, 90);
	m_coinText->SetSpacing(14);
	m_coinText->SetSize(24);

	Game::CurrentScene->Add(m_waveTitle);
	Game::CurrentScene->Add(m_waveTimerText);
	Game::CurrentScene->Add(m_healthBar);
	Game::CurrentScene->Add(m_expBar);
	Game::CurrentScene->Add(m_hpText);
	Game::CurrentScene->Add(m_levelText);
	Game::CurrentScene->Add(m_coinIcon);
	Game::CurrentScene->Add(m_coinText);

	m_healthBar->FadeIn(0.5f);
	m_expBar->FadeIn(0.5f);


	m_moneyDropsMnger = new DropsManager(20);

	EnemyHealthEventDispatcher::Attach(this);
	PlayerLevelUpEventDispatcher::Attach(this);
	CoinCollectEventDistpacher::Attach(this);
}

void GameplayState::Update(float deltaTime)
{
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
				//TODO:Do somethings
				m_minute = 0;
			}
		}
		m_waveTimerText->SetText(GetFormatedTime());
	}

	
	m_enemySpawner->Update(deltaTime);

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
	EnemyHealthEventDispatcher::Detach(this);
	PlayerLevelUpEventDispatcher::Detach(this);
	CoinCollectEventDistpacher::Detach(this);
}

void GameplayState::OnTriggerEvent(const LevelUpEvent& eventType)
{
	m_levelTxtValue = "Lv " + std::to_string(m_player->XPController().GetCurrentLv());
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
}


