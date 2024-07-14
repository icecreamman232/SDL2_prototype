#include "EndWaveState.h"
#include "Game.h"
#include "TweenManager.h"
#include "Timer.h"
#include "GameStateManager.h"
#include "PickUpgradeEventDispatcher.h"

void EndWaveState::Initialize(GameStateManager* manager)
{
	m_manager = manager;

	m_chooseUpgradeBtn.Init("ChooseUpgradeBtn",Render::TEXTURE_ID::WHITE_BAR_UI
		,g_WindowSettings.Width/2-200/2, g_WindowSettings.Height - 50/2-80, 200, 50);
	m_chooseUpgradeBtn.FillColor(SDL_Color{ 0,255,0,255 });
	
	m_chooseUpgradeBtn.SetCallBack(std::bind(&EndWaveState::OnChosenPowerUp, this));

	InitializePowerUp();
	InitializePowerUpCard();

	//Coin icon
	m_coinIcon = new UIImage();
	m_coinIcon->Init("CoinIcon",Render::TEXTURE_ID::COIN, 15, 40, 60, 60);

	//Number coin text
	m_coinText.Initialize(TEXTURE_ID::BM_FONT_PIXEL, std::to_string(m_coinAmount), Render::Pivot::CENTER, 70, 60);
	m_coinText.SetSpacing(14);
	m_coinText.SetSize(24);

	Game::CurrentScene->Add(m_coinIcon);
	Game::CurrentScene->Add(&m_coinText);

	m_isRunning = true;
}

void EndWaveState::InitializePowerUp()
{
	PowerUpType powerUpLeftType = m_manager->GetPowerUpManager()->GetRandomPowerUp();
	m_powerUpLeft.Initialize(powerUpLeftType);

	PowerUpType powerUpMidType = m_manager->GetPowerUpManager()->GetRandomPowerUp();
	m_powerUpMid.Initialize(powerUpMidType);

	PowerUpType powerUpRightType = m_manager->GetPowerUpManager()->GetRandomPowerUp();
	m_powerUpRight.Initialize(powerUpRightType);
}

void EndWaveState::InitializePowerUpCard()
{
	int padding = 80;
	int width = 300;
	int height = 450;
	int offsetToTween = 100;
	m_upgradeCard_Left.Init("UpgradeCardLeft", Render::TEXTURE_ID::WHITE_BAR_UI,
		padding, g_WindowSettings.Height / 2 - height / 2 - offsetToTween,
		width, height);
	m_upgradeCard_Left.FillColor(SDL_Color{0,162,232,255});

	m_upgradeCard_Mid.Init("UpgradeCardMid",Render::TEXTURE_ID::WHITE_BAR_UI,
		g_WindowSettings.Width / 2 - width / 2, g_WindowSettings.Height / 2 - height / 2 - offsetToTween,
		width, height);
	m_upgradeCard_Mid.FillColor(SDL_Color{ 0,162,232,255});

	m_upgradeCard_Right.Init("UpgradeCardRight",Render::TEXTURE_ID::WHITE_BAR_UI,
		g_WindowSettings.Width - padding - width, g_WindowSettings.Height / 2 - height / 2 - offsetToTween,
		width, height);
	m_upgradeCard_Right.FillColor(SDL_Color{ 0,162,232,255});

	m_upgradeCard_Left.AssignEndWaveStateRef(this);
	m_upgradeCard_Mid.AssignEndWaveStateRef(this);
	m_upgradeCard_Right.AssignEndWaveStateRef(this);

	m_upgradeCard_Left.SetInteract(false);
	m_upgradeCard_Mid.SetInteract(false);
	m_upgradeCard_Right.SetInteract(false);


	m_upgradeCard_Left.AssignChooseUpgradeButton(&m_chooseUpgradeBtn);
	m_upgradeCard_Mid.AssignChooseUpgradeButton(&m_chooseUpgradeBtn);
	m_upgradeCard_Right.AssignChooseUpgradeButton(&m_chooseUpgradeBtn);

	Game::CurrentScene->Add(&m_upgradeCard_Left);
	Game::CurrentScene->Add(&m_upgradeCard_Mid);
	Game::CurrentScene->Add(&m_upgradeCard_Right);

	m_upgradeCard_Left.AssignCardValue(m_powerUpLeft.GetPU_Type());
	m_upgradeCard_Mid.AssignCardValue(m_powerUpMid.GetPU_Type());
	m_upgradeCard_Right.AssignCardValue(m_powerUpRight.GetPU_Type());

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
}

void EndWaveState::OnTriggerEvent(const PickUpgradeEvent& eventType)
{

}

void EndWaveState::Update(float deltaTime)
{
	if (!m_isRunning) return;
	m_upgradeCard_Left.Update();
	m_upgradeCard_Mid.Update();
	m_upgradeCard_Right.Update();

	m_chooseUpgradeBtn.Update();

	if (m_coinIcon != nullptr)
	{
		m_coinIcon->Update();
	}

}

void EndWaveState::Render()
{

}

void EndWaveState::ExitState()
{
	std::cout << "Exit:EndWaveState" << std::endl;

	m_isRunning = false;

	m_chooseUpgradeBtn.CleanUp();

	PickUpgradeEventDispatcher::Detach(this);

	//Prevent unexpected interaction while exiting
	m_upgradeCard_Left.SetInteract(false);
	m_upgradeCard_Mid.SetInteract(false);
	m_upgradeCard_Right.SetInteract(false);


	Game::CurrentScene->Remove(&m_upgradeCard_Left);
	Game::CurrentScene->Remove(&m_upgradeCard_Mid);
	Game::CurrentScene->Remove(&m_upgradeCard_Right);

	m_upgradeCard_Left.CleanUp();
	m_upgradeCard_Mid.CleanUp();
	m_upgradeCard_Right.CleanUp();

	Game::CurrentScene->Remove(m_coinIcon);
	Game::CurrentScene->Remove(&m_coinText);

	delete m_coinIcon;
	m_coinIcon = nullptr;
}

void EndWaveState::OnFinishOpeningTween()
{

	m_chooseUpgradeBtn.SetInteract(true);

	m_upgradeCard_Left.SetInteract(true);
	m_upgradeCard_Left.OnFinishTween();
	

	m_upgradeCard_Mid.SetInteract(true);
	m_upgradeCard_Mid.OnFinishTween();

	m_upgradeCard_Right.SetInteract(true);
	m_upgradeCard_Right.OnFinishTween();
}

void EndWaveState::OnChosenPowerUp()
{
	std::cout << "Player's chosen powerup:" << std::endl;
	ExitState();
}
