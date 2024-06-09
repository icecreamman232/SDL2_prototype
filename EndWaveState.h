#pragma once

#include "GameState.h"

class EndWaveState : public GameState
{
	void Initialize(GameStateManager* manager) override;
	void Update(float deltaTime) override;
	void Render() override;
	void ExitState() override;
};

