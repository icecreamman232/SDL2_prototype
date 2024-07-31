#pragma once
#include "GameState.h"
#include "BMTextRenderer.h"
#include "MenuButton.h"

class GameStateManager;

class GameOverState : public GameState
{
public:
	void Initialize(GameStateManager* manager) override;
	void Update(float deltaTime) override;
	void Render() override;
	void ExitState() override;

private:
	void OnBackToMainMenu();
	void OnStartNewGame();


	BMTextRenderer m_gameoverTitleTxt;

	MenuButton m_backToMainMenuBtn;
	MenuButton m_newGameBtn;
};

