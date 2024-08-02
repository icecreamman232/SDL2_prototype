#include "GameOverState.h"
#include "Timer.h"
#include "Game.h"

void GameOverState::Initialize(GameStateManager* manager)
{
	m_manager = manager;
	m_shouldExitNextFrame = false;

	m_gameoverTitleTxt.Initialize(Render::BM_FONT_PIXEL, 
		"GAME OVER", Render::Pivot::CENTER,0, 0);
	m_gameoverTitleTxt.SetSize(16*10);
	m_gameoverTitleTxt.SetSpacing(20);
	m_gameoverTitleTxt.SetPosition(g_WindowSettings.Width/2, 16*10);
	

	Game::CurrentScene->Add(&m_gameoverTitleTxt);


	m_backToMainMenuBtn.Init("Main Menu", Render::TEXTURE_ID::WHITE_BAR_UI
		, 200, g_WindowSettings.Height - 200, 300, 60);
	m_backToMainMenuBtn.SetTextPosition(200 + 130, g_WindowSettings.Height - 200 + 40);
	m_backToMainMenuBtn.SetButtonTextSize(16*2);
	m_backToMainMenuBtn.SetButtonTextSpacing(5);
	m_backToMainMenuBtn.FillColor(SDL_Color{ 0,0,0,255 });
	m_backToMainMenuBtn.SetCallBack(std::bind(&GameOverState::OnBackToMainMenu, this));


	m_newGameBtn.Init("New Game", Render::TEXTURE_ID::WHITE_BAR_UI
		, g_WindowSettings.Width - 300 - 200, g_WindowSettings.Height - 200, 300, 60);
	m_newGameBtn.SetTextPosition(g_WindowSettings.Width - 365, g_WindowSettings.Height - 200 + 40);
	m_newGameBtn.SetButtonTextSize(16 * 2);
	m_newGameBtn.SetButtonTextSpacing(5);
	m_newGameBtn.FillColor(SDL_Color{ 34,177,76,255 });
	m_newGameBtn.SetCallBack(std::bind(&GameOverState::OnStartNewGame, this));


	m_isRunning = true;
}

void GameOverState::Update(float deltaTime)
{
	if (m_shouldExitNextFrame)
	{
		m_shouldExitNextFrame = false;
		ExitState();
		return;
	}

	if (!m_isRunning) return;

	m_gameoverTitleTxt.Update();
	m_backToMainMenuBtn.Update();
	m_newGameBtn.Update();

}

void GameOverState::Render()
{

}

void GameOverState::ExitState()
{
	m_isRunning = false;
	Game::CurrentScene->Remove(&m_gameoverTitleTxt);
	m_backToMainMenuBtn.CleanUp();
	m_newGameBtn.CleanUp();

	m_manager->BeginChangeState();
	m_manager->ChangeState(General::GameStateType::GAMEPLAY);
}

void GameOverState::OnBackToMainMenu()
{
	std::cout << "Back to Main Menu" << std::endl;
}

void GameOverState::OnStartNewGame()
{
	std::cout << "Start New Game" << std::endl;
	m_shouldExitNextFrame = true;
}

