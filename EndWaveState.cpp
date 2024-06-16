#include "EndWaveState.h"
#include "Game.h"
#include "TweenManager.h"
#include "Timer.h"

void EndWaveState::Initialize(GameStateManager* manager)
{
	int padding = 80;
	int width = 300;
	int height = 450;
	int offsetToTween = 100;
	m_upgradeCard_Left.Init(Render::TEXTURE_ID::WHITE_BAR_UI,
		padding, g_WindowSettings.Height / 2 - height/2 - offsetToTween,
		width, height);

	m_upgradeCard_Mid.Init(Render::TEXTURE_ID::WHITE_BAR_UI, 
		g_WindowSettings.Width/2 - width /2, g_WindowSettings.Height / 2 - height/2 - offsetToTween,
		width, height);

	m_upgradeCard_Right.Init(Render::TEXTURE_ID::WHITE_BAR_UI,
		g_WindowSettings.Width - padding - width, g_WindowSettings.Height / 2 - height/2 - offsetToTween,
		width, height);

	m_upgradeCard_Left.AssignEndWaveStateRef(this);
	m_upgradeCard_Mid.AssignEndWaveStateRef(this);
	m_upgradeCard_Right.AssignEndWaveStateRef(this);

	m_upgradeCard_Left.SetInteract(false);
	m_upgradeCard_Mid.SetInteract(false);
	m_upgradeCard_Right.SetInteract(false);

	Game::CurrentScene->Add(&m_upgradeCard_Left);
	Game::CurrentScene->Add(&m_upgradeCard_Mid);
	Game::CurrentScene->Add(&m_upgradeCard_Right);

	m_leftOpeningTween = TweenManager::Instance().CreateTween(Tween::TweenEase::OUT_QUINT,
		&m_upgradeCard_Left, padding, m_upgradeCard_Left.GetPosY() + offsetToTween, 1.0f);

	m_midOpeningTween = TweenManager::Instance().CreateTween(Tween::TweenEase::OUT_QUINT,
		&m_upgradeCard_Mid, g_WindowSettings.Width / 2 - width / 2, m_upgradeCard_Mid.GetPosY() + offsetToTween, 1.2f);

	m_rightOpeningTween = TweenManager::Instance().CreateTween(Tween::TweenEase::OUT_QUINT,
		&m_upgradeCard_Right, g_WindowSettings.Width - padding - width, m_upgradeCard_Right.GetPosY() + offsetToTween, 1.5f);


	m_upgradeCard_Left.SetOriginal_Y(m_upgradeCard_Left.GetPosY() + offsetToTween);
	m_upgradeCard_Mid.SetOriginal_Y(m_upgradeCard_Mid.GetPosY() + offsetToTween);
	m_upgradeCard_Right.SetOriginal_Y(m_upgradeCard_Right.GetPosY() + offsetToTween);

	Timer* timer = new Timer(1.5f, std::bind(&EndWaveState::OnFinishOpeningTween, this));


	//Coin icon
	m_coinIcon = new UIImage();
	m_coinIcon->Init(Render::TEXTURE_ID::COIN, 15, 40, 60, 60);

	//Number coin text
	m_coinText.Initialize(TEXTURE_ID::BM_FONT_PIXEL, std::to_string(m_coinAmount), Render::Pivot::CENTER, 70, 60);
	m_coinText.SetSpacing(14);
	m_coinText.SetSize(24);

	Game::CurrentScene->Add(m_coinIcon);
	Game::CurrentScene->Add(&m_coinText);

	m_isRunning = true;
}

void EndWaveState::Update(float deltaTime)
{
	m_upgradeCard_Left.Update();
	m_upgradeCard_Mid.Update();
	m_upgradeCard_Right.Update();

	m_coinIcon->Update();
}

void EndWaveState::Render()
{

}

void EndWaveState::ExitState()
{

}

void EndWaveState::OnFinishOpeningTween()
{
	m_upgradeCard_Left.SetInteract(true);
	m_upgradeCard_Mid.SetInteract(true);
	m_upgradeCard_Right.SetInteract(true);
}
