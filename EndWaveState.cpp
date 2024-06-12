#include "EndWaveState.h"
#include "Game.h"
#include "TweenManager.h"

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

	Game::CurrentScene->Add(&m_upgradeCard_Left);
	Game::CurrentScene->Add(&m_upgradeCard_Mid);
	Game::CurrentScene->Add(&m_upgradeCard_Right);

	TweenManager::Instance().CreateTween(Tween::TweenEase::OUT_QUINT,
		&m_upgradeCard_Left, padding, m_upgradeCard_Left.GetPosY() + offsetToTween, 1.0f);

	TweenManager::Instance().CreateTween(Tween::TweenEase::OUT_QUINT,
		&m_upgradeCard_Mid, g_WindowSettings.Width / 2 - width / 2, m_upgradeCard_Mid.GetPosY() + offsetToTween, 1.2f);

	TweenManager::Instance().CreateTween(Tween::TweenEase::OUT_QUINT,
		&m_upgradeCard_Right, g_WindowSettings.Width - padding - width, m_upgradeCard_Right.GetPosY() + offsetToTween, 1.5f);

	m_isRunning = true;
}

void EndWaveState::Update(float deltaTime)
{
	m_upgradeCard_Left.Update();
	m_upgradeCard_Mid.Update();
	m_upgradeCard_Right.Update();

}

void EndWaveState::Render()
{

}

void EndWaveState::ExitState()
{

}
