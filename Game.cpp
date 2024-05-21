#include "Game.h"
#include "SDL_image.h"
#include "GameObject.h"
#include "Input.h"

int Game::ScreenWidth = 0;
int Game::ScreenHeight = 0;

SDL_Renderer* Game::Renderer = nullptr;

Game::Game()
{
	m_healthBar = nullptr;
	Input::Instance().Initialize();
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
		Renderer = SDL_CreateRenderer(m_window, -1, 0);
		if (Renderer)
		{
			SDL_SetRenderDrawColor(Renderer, 31, 31, 31, 255);
			std::cout << "Renderer created..." << std::endl;
			m_isRunning = true;
		}
		else {
			m_isRunning = false;
		}
	}

	SDL_GetWindowSize(m_window, &ScreenWidth, &ScreenHeight);
	AssetManager::Instance().Initialize();
	m_healthBar = new PlayerHealthBar(20, 20, 200, 20);

	m_enemy = new Slime(1,"enemy", SLIME_TEX, 0, 0, 16, 16);
	m_enemy->SetLayer(Layer::ENEMY);

	m_enemy1 = new Slime(2,"enemy1",SLIME_TEX, 0, 100, 16, 16);
	m_enemy1->SetLayer(Layer::ENEMY);

	m_enemy2 = new Slime(3,"enemy2", SLIME_TEX, 100, 0, 16, 16);
	m_enemy2->SetLayer(Layer::ENEMY);

	m_enemy3 = new Slime(4,"enemy3",SLIME_TEX, 1110, 100, 16, 16);
	m_enemy3->SetLayer(Layer::ENEMY);

	m_enemy4 = new Slime(5,"enemy4",SLIME_TEX, 800, 500, 16, 16);
	m_enemy4->SetLayer(Layer::ENEMY);

	m_enemy5 = new Slime(6,"enemy5",SLIME_TEX, 1000, 300, 16, 16);
	m_enemy5->SetLayer(Layer::ENEMY);

	m_enemy6 = new Slime(7,"enemy6",SLIME_TEX, 300, 600, 16, 16);
	m_enemy6->SetLayer(Layer::ENEMY);

	m_enemy7 = new Slime(8,"enemy7",SLIME_TEX, 500, 600, 16, 16);
	m_enemy7->SetLayer(Layer::ENEMY);


	m_player = new SpaceShip("Ship",PLAYER_TEX, 300, 300, 18, 16);
	m_player->SetLayer(Layer::PLAYER);

	m_quadTreev2 = new QuadTreev2(SDL_FRect{ 0.0,0.0,static_cast<float>(ScreenWidth) ,static_cast<float>(ScreenHeight) }, 0, 0);

	m_quadTreev2->Insert(m_player);
	m_quadTreev2->Insert(m_enemy);
	m_quadTreev2->Insert(m_enemy1);
	m_quadTreev2->Insert(m_enemy2);
	m_quadTreev2->Insert(m_enemy3);
	m_quadTreev2->Insert(m_enemy4);
	m_quadTreev2->Insert(m_enemy5);
	m_quadTreev2->Insert(m_enemy6);
	m_quadTreev2->Insert(m_enemy7);
}

void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	Input::Instance().HandleEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
			m_isRunning = false;
			break;
	}
}

void Game::Update(float deltaTime)
{
	m_player->Update(deltaTime);
	m_enemy->Update(deltaTime);
	m_enemy1->Update(deltaTime);
	m_enemy2->Update(deltaTime);
	m_enemy3->Update(deltaTime);
	m_enemy4->Update(deltaTime);
	m_enemy5->Update(deltaTime);
	m_enemy6->Update(deltaTime);
	m_enemy7->Update(deltaTime);

	m_quadTreev2 = new QuadTreev2(SDL_FRect{ 0.0,0.0,static_cast<float>(ScreenWidth) ,static_cast<float>(ScreenHeight) }, 0, 0);

	m_quadTreev2->Insert(m_player);
	m_quadTreev2->Insert(m_enemy);
	m_quadTreev2->Insert(m_enemy1);
	m_quadTreev2->Insert(m_enemy2);
	m_quadTreev2->Insert(m_enemy3);
	m_quadTreev2->Insert(m_enemy4);
	m_quadTreev2->Insert(m_enemy5);
	m_quadTreev2->Insert(m_enemy6);
	m_quadTreev2->Insert(m_enemy7);

	m_healthBar->UpdateBar(m_player->GetPercentHealth());


	auto result = m_quadTreev2->GetCollision(m_player);
	if (result != nullptr)
	{
		m_player->TakeDamage();
	}
}


void Game::Render(float deltaTime)
{
	//m_quadTree->Render(m_renderer);
	SDL_SetRenderDrawColor(Renderer, 31, 31, 31, 255);
	SDL_RenderClear(Renderer);

	
	m_player->Render();
	m_enemy->Render();
	m_enemy1->Render();
	m_enemy2->Render();
	m_enemy3->Render();
	m_enemy4->Render();
	m_enemy5->Render();
	m_enemy6->Render();
	m_enemy7->Render();

	m_quadTreev2->Render(Renderer);
	
	m_healthBar->Render();

	SDL_RenderPresent(Renderer);
}


void Game::Clean()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(Renderer);
	SDL_Quit();
	std::cout << "Cleaned and quit..." << std::endl;
}

bool Game::IsRunning()
{
	return m_isRunning;
}