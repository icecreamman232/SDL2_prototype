#pragma once
#include "GameState.h"
#include "BMTextRenderer.h"
#include "UIImage.h"
#include "TweenEffect.h"
#include "UpgradeCard.h"
#include "ChooseUpgradeButton.h"
#include "PowerUpBase.h"
#include "ISubscriber.h"
#include "PickUpgradeEventDispatcher.h"

class EndWaveState : public GameState,
	public ISubscriber<PickUpgradeEvent>
{
public:
	void Initialize(GameStateManager* manager) override;
	void InitializePowerUp();
	void InitializePowerUpCard();

	void OnTriggerEvent(const PickUpgradeEvent& eventType) override;

	void Update(float deltaTime) override;
	void Render() override;
	void ExitState() override;
	void OnFinishOpeningTween();


private:

	void OnChosenPowerUp();
	
	bool m_exitNextFrame = false;

	GameStateManager* m_manager;

	UpgradeCard m_upgradeCard_Left;
	UpgradeCard m_upgradeCard_Mid;
	UpgradeCard m_upgradeCard_Right;

	ChooseUpgradeButton m_chooseUpgradeBtn;

	BMTextRenderer m_coinText;
	UIImage* m_coinIcon;

	TweenUIPosition* m_leftOpeningTween;
	TweenUIPosition* m_midOpeningTween;
	TweenUIPosition* m_rightOpeningTween;

	int m_coinAmount;
	PowerUpBase m_powerUpLeft;
	PowerUpBase m_powerUpMid;
	PowerUpBase m_powerUpRight;
};

