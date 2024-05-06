#include "Game.h"
#include "SDL_image.h"
#include "GameObject.h"

int Game::ScreenWidth = 0;
int Game::ScreenHeight = 0;

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
			SDL_SetRenderDrawColor(m_renderer, 31, 31, 31, 255);
			std::cout << "Renderer created..." << std::endl;
			m_isRunning = true;
		}
		else {
			m_isRunning = false;
		}
	}

	SDL_GetWindowSize(m_window, &ScreenWidth, &ScreenHeight);

	m_enemy = new GameObject("enemy", "Asset/space-slime.png", m_renderer, 0, 0, 16, 16);
	m_enemy1 = new GameObject("enemy1", "Asset/space-slime.png", m_renderer, 300, 100, 16, 16);
	m_enemy2 = new GameObject("enemy2","Asset/space-slime.png", m_renderer, 200, 300, 16, 16);
	m_enemy3 = new GameObject("enemy3","Asset/space-slime.png", m_renderer, 500, 700, 16, 16);
	m_enemy4 = new GameObject("enemy4","Asset/space-slime.png", m_renderer, 800, 500, 16, 16);
	m_enemy5 = new GameObject("enemy5", "Asset/space-slime.png", m_renderer, 1000, 300, 16, 16);


	m_player = new SpaceShip("Ship","Asset/blue-starship.png", m_renderer, 300, 300, 18, 16);


	m_quadTree = new QuadTree(SDL_FRect{ 0.0,0.0,static_cast<float>(ScreenWidth), static_cast<float>(ScreenHeight) }
	, 255, 0, 0);
	m_quadTree->Insert(*m_enemy);
	m_quadTree->Insert(*m_enemy1);
	m_quadTree->Insert(*m_enemy2);
	m_quadTree->Insert(*m_enemy3);
	m_quadTree->Insert(*m_enemy4);
	m_quadTree->Insert(*m_enemy5);
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

void Game::Update(float deltaTime)
{
	m_player->LookAt(m_input->MouseX, m_input->MouseY);

	if (m_input->GetKeyDown(SDL_SCANCODE_A))
	{
		m_player->SetDirectionX(-1.0);
	}
	else if (m_input->GetKeyDown(SDL_SCANCODE_D))
	{
		m_player->SetDirectionX(1.0);
	}
	else 
	{
		m_player->SetDirectionX(0.0);
	}


	if (m_input->GetKeyDown(SDL_SCANCODE_W))
	{
		m_player->SetDirectionY(-1.0);
	}
	else if (m_input->GetKeyDown(SDL_SCANCODE_S))
	{
		m_player->SetDirectionY(1.0);
	}
	else 
	{
		m_player->SetDirectionY(0.0);
	}

	m_player->Update(deltaTime);
	m_enemy->Update(deltaTime);
	m_enemy1->Update(deltaTime);
	m_enemy2->Update(deltaTime);
	m_enemy3->Update(deltaTime);
	m_enemy4->Update(deltaTime);
	m_enemy5->Update(deltaTime);

	m_quadTree->Update();

	/*m_quadTree->Update(*m_enemy);
	m_quadTree->Update(*m_enemy1);
	m_quadTree->Update(*m_enemy2);
	m_quadTree->Update(*m_enemy3);
	m_quadTree->Update(*m_enemy4);
	m_quadTree->Update(*m_enemy5);*/


	m_collisionList = m_quadTree->CheckCollision(*m_player);
	if (!m_collisionList.empty())
	{
		std::cout << "HIT" << std::endl;
	}
	else 
	{
		std::cout << "No" << std::endl;
	}

}


void Game::Render(float deltaTime)
{
	SDL_RenderClear(m_renderer);

	m_quadTree->Render(m_renderer);
	m_player->Render();
	m_enemy->Render();
	m_enemy1->Render();
	m_enemy2->Render();
	m_enemy3->Render();
	m_enemy4->Render();
	m_enemy5->Render();

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