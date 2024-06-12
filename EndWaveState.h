#pragma once
#include "GameState.h"
#include "UIImage.h"

class EndWaveState : public GameState
{
public:
	void Initialize(GameStateManager* manager) override;
	void Update(float deltaTime) override;
	void Render() override;
	void ExitState() override;
private:
	UIImage m_upgradeCard_Left;
	UIImage m_upgradeCard_Mid;
	UIImage m_upgradeCard_Right;
};

