#pragma once
#include "GameState.h"

class GameStateManager;

class GameOverState : public GameState
{
public:
	void Initialize(GameStateManager* manager) override;
	void Update(float deltaTime) override;
	void Render() override;
	void ExitState() override;

private:

};

