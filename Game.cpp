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

	m_enemy = new Slime(1,"enemy", "Asset/space-slime.png", m_renderer, 0, 0, 16, 16);
	m_enemy1 = new Slime(2,"enemy1", "Asset/space-slime.png", m_renderer, 0, 100, 16, 16);
	m_enemy2 = new Slime(3,"enemy2","Asset/space-slime.png", m_renderer, 100, 0, 16, 16);
	m_enemy3 = new Slime(4,"enemy3","Asset/space-slime.png", m_renderer, 1110, 100, 16, 16);
	m_enemy4 = new Slime(5,"enemy4","Asset/space-slime.png", m_renderer, 800, 500, 16, 16);
	m_enemy5 = new Slime(6,"enemy5", "Asset/space-slime.png", m_renderer, 1000, 300, 16, 16);


	m_player = new SpaceShip("Ship","Asset/blue-starship.png", m_renderer, 300, 300, 18, 16);


	m_quadTreev2 = new QuadTreev2(SDL_FRect{ 0.0,0.0,static_cast<float>(ScreenWidth) ,static_cast<float>(ScreenHeight) }, 0, 0);

	m_quadTreev2->Insert(m_player);
	m_quadTreev2->Insert(m_enemy);
	m_quadTreev2->Insert(m_enemy1);
	m_quadTreev2->Insert(m_enemy2);
	m_quadTreev2->Insert(m_enemy3);
	m_quadTreev2->Insert(m_enemy4);
	m_quadTreev2->Insert(m_enemy5);


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

	m_quadTreev2 = new QuadTreev2(SDL_FRect{ 0.0,0.0,static_cast<float>(ScreenWidth) ,static_cast<float>(ScreenHeight) }, 0, 0);

	m_quadTreev2->Insert(m_player);
	m_quadTreev2->Insert(m_enemy);
	m_quadTreev2->Insert(m_enemy1);
	m_quadTreev2->Insert(m_enemy2);
	m_quadTreev2->Insert(m_enemy3);
	m_quadTreev2->Insert(m_enemy4);
	m_quadTreev2->Insert(m_enemy5);


	auto result = m_quadTreev2->CheckCollision(m_player);
	if (result.size() > 0)
	{
		for (int i = 0; i < result.size(); i++)
		{
			std::cout << "HIT " << result[i]->GetName() << std::endl;
		}
	}


}


void Game::Render(float deltaTime)
{
	//m_quadTree->Render(m_renderer);
	SDL_SetRenderDrawColor(m_renderer, 31, 31, 31, 255);
	SDL_RenderClear(m_renderer);

	
	m_player->Render();
	m_enemy->Render();
	m_enemy1->Render();
	m_enemy2->Render();
	m_enemy3->Render();
	m_enemy4->Render();
	m_enemy5->Render();

	m_quadTreev2->Render(m_renderer);
	
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