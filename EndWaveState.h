#pragma once
#include "GameState.h"
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

	TweenEffect* m_leftOpeningTween;
	TweenEffect* m_midOpeningTween;
	TweenEffect* m_rightOpeningTween;
};

