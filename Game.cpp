#include "Game.h"
#include "SDL_image.h"
#include "GameObject.h"

GameObject* player = nullptr;

Game::Game()
{
	m_input = new Input();
}

Game::~Game()
{

}

void Game::Init(const char* title, int x, int y, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Initialized..." << std::endl;
		m_window = SDL_CreateWindow("Prototype", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, SDL_WINDOW_SHOWN);
		m_renderer = SDL_CreateRenderer(m_window, -1, 0);
		if (m_renderer)
		{
			SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
			std::cout << "Renderer created..." << std::endl;
			m_isRunning = true;
		}
		else {
			m_isRunning = false;
		}
	}
	

	player = new GameObject("Asset/blue-starship.png", m_renderer, 200,300);
}

void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	m_input->HandleEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
			m_isRunning = false;
			break;
	}
}

void Game::Update()
{
	player->Update();
}


void Game::Render()
{
	SDL_RenderClear(m_renderer);

	player->Render();
	//if (m_input->IsLeftMouseDown())
	{
		
		//player->SetPosition(m_input->MouseX,m_input->MouseY);
		player->LookAt(m_input->MouseX, m_input->MouseY);
	}

	SDL_RenderPresent(m_renderer);
}


void Game::Clean()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
	std::cout << "Cleaned and quit..." << std::endl;
}

bool Game::IsRunning()
{
	return m_isRunning;
}