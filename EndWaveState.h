#pragma once
#include "GameState.h"
#include "BMTextRenderer.h"
#include "UIImage.h"
#include "TweenEffect.h"
#include "UpgradeCard.h"

class EndWaveState : public GameState
{
public:
	void Initialize(GameStateManager* manager) override;
	void Update(float deltaTime) override;
	void Render() override;
	void ExitState() override;
	void OnFinishOpeningTween();
private:
	UpgradeCard m_upgradeCard_Left;
	UpgradeCard m_upgradeCard_Mid;
	UpgradeCard m_upgradeCard_Right;


	BMTextRenderer m_coinText;
	UIImage* m_coinIcon;

	TweenEffect* m_leftOpeningTween;
	TweenEffect* m_midOpeningTween;
	TweenEffect* m_rightOpeningTween;

	int m_coinAmount;
};

