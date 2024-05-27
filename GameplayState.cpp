#include "GameplayState.h"
#include "Game.h"
#include <iostream>
#include "GameStateManager.h"
#include <string>
#include <sstream>
#include "Slime.h"	

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

	m_healthBar = new PlayerHealthBar(20, 20, 200, 20);

	auto title = "WAVE " + std::to_string(m_manager->GetCurrentWaveIndex());
	m_waveTitle = new BMTextRenderer(TEXTURE_ID::BM_FONT_PIXEL, title, Render::Pivot::CENTER, Game::ScreenWidth / 2, 10);
	m_waveTitle->SetSpacing(20);
	m_waveTitle->SetSize(32);

	m_waveTimerText = new BMTextRenderer(TEXTURE_ID::BM_FONT_PIXEL, GetFormatedTime(), Render::Pivot::CENTER, Game::ScreenWidth / 2 + 15, 50);
	m_waveTimerText->SetSpacing(16);
	m_waveTimerText->SetSize(24);

	Game::CurrentScene->Add(m_waveTitle);
	Game::CurrentScene->Add(m_waveTimerText);
	Game::CurrentScene->Add(m_healthBar);

	m_healthBar->FadeIn(0.5f);
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
	m_healthBar->UpdateBar(m_player->GetPercentHealth());

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

}

void GameplayState::Render()
{
	
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


