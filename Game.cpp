#include "Game.h"
#include "SDL_image.h"
#include "GameObject.h"
#include "Input.h"


int Game::ScreenWidth = 0;
int Game::ScreenHeight = 0;
SDL_Renderer* Game::Renderer = nullptr;
Scene* Game::CurrentScene = nullptr;
QuadTreev2* Game::m_quadTreev2 = nullptr;

using namespace General;

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

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
		// From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
		SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif
		std::cout << "Initialized..." << std::endl;
		SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
		m_window = SDL_CreateWindow("Prototype", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, window_flags);
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

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048))
		{
			std::cout << "SDL_mixer could not initialize! SDL_mixer Error:" << Mix_GetError() << std::endl;
			m_isRunning = false;
		}
	}


	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	auto context = ImGui::CreateContext();
	//ImGui::SetCurrentContext(context);
	io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForSDLRenderer(m_window, Renderer);
	ImGui_ImplSDLRenderer2_Init(Renderer);

	m_FPSOverlayWindownFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking 
		| ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings 
		| ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
	m_showFPSOverlay = false;

	SDL_GetWindowSize(m_window, &ScreenWidth, &ScreenHeight);

	music = Mix_LoadMUS("Asset/Music/DaniStob-OverdriveSunset-Loop.wav");

	AssetManager::Instance().Initialize();
	CurrentScene = new Scene();



	m_healthBar = new PlayerHealthBar(20, 20, 200, 20);

	m_enemy = new Slime("enemy", SLIME_TEX, 0, 0, 16, 16,0);
	m_enemy->SetLayer(Layer::ENEMY);

	m_enemy1 = new Slime("enemy1",SLIME_TEX, 0, 100, 16, 16,1);
	m_enemy1->SetLayer(Layer::ENEMY);

	m_enemy2 = new Slime("enemy2", SLIME_TEX, 100, 0, 16, 16,2);
	m_enemy2->SetLayer(Layer::ENEMY);

	m_enemy3 = new Slime("enemy3",SLIME_TEX, 1110, 100, 16, 16,3);
	m_enemy3->SetLayer(Layer::ENEMY);

	m_enemy4 = new Slime("enemy4",SLIME_TEX, 800, 500, 16, 16,4);
	m_enemy4->SetLayer(Layer::ENEMY);

	m_enemy5 = new Slime("enemy5",SLIME_TEX, 1000, 300, 16, 16,5);
	m_enemy5->SetLayer(Layer::ENEMY);

	m_enemy6 = new Slime("enemy6",SLIME_TEX, 300, 600, 16, 16,7);
	m_enemy6->SetLayer(Layer::ENEMY);

	m_enemy7 = new Slime("enemy7",SLIME_TEX, 500, 600, 16, 16,6);
	m_enemy7->SetLayer(Layer::ENEMY);


	m_player = new SpaceShip("Ship",PLAYER_TEX, 300, 300, 18, 16,9);
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


	//Add game object to current scene
	CurrentScene->Add(m_enemy, RenderLayer::ENEMY);
	CurrentScene->Add(m_enemy1, RenderLayer::ENEMY);
	CurrentScene->Add(m_enemy2, RenderLayer::ENEMY);
	CurrentScene->Add(m_enemy3, RenderLayer::ENEMY);
	CurrentScene->Add(m_enemy4, RenderLayer::ENEMY);
	CurrentScene->Add(m_enemy5, RenderLayer::ENEMY);
	CurrentScene->Add(m_enemy6, RenderLayer::ENEMY);
	CurrentScene->Add(m_enemy7, RenderLayer::ENEMY);
	CurrentScene->Add(m_player, RenderLayer::ENEMY);

	//Mix_PlayMusic(music, -1);
	Mix_FadeInMusic(music, -1, 1500);
	while (Mix_FadingMusic() == MIX_FADING_IN)
	{
		SDL_Delay(30);
	}
}

void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	ImGui_ImplSDL2_ProcessEvent(&event);
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

	m_enemy->Update(deltaTime);
	m_enemy1->Update(deltaTime);
	m_enemy2->Update(deltaTime);
	m_enemy3->Update(deltaTime);
	m_enemy4->Update(deltaTime);
	m_enemy5->Update(deltaTime);
	m_enemy6->Update(deltaTime);
	m_enemy7->Update(deltaTime);
	m_player->Update(deltaTime);

	m_healthBar->UpdateBar(m_player->GetPercentHealth());


	auto result = m_quadTreev2->GetCollision(m_player, Layer::ENEMY);
	if (result != nullptr)
	{
		auto slime = dynamic_cast<Slime*>(result);
		if (slime != nullptr)
		{
			m_player->TakeDamage(slime->GetDamage());
		}
	}

	//Toggle the FPS Overlay
	if (Input::Instance().GetKeyPressed(SDL_Scancode::SDL_SCANCODE_P))
	{
		m_showFPSOverlay = !m_showFPSOverlay;
	}
}

void Game::RenderImGUI()
{
	// Start the Dear ImGui frame
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();


	io = ImGui::GetIO();
	m_viewport = ImGui::GetMainViewport();
	ImVec2 work_pos = m_viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
	ImVec2 work_size = m_viewport->WorkSize;
	ImVec2 window_pos, window_pos_pivot;
	window_pos.x = work_pos.x + work_size.x - PAD;
	window_pos.y = work_pos.y + PAD;
	window_pos_pivot.x = 1.0f;
	window_pos_pivot.y = 0.0f;
	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	ImGui::SetNextWindowViewport(m_viewport->ID);
	m_FPSOverlayWindownFlags |= ImGuiWindowFlags_NoMove;

	if (ImGui::Begin("FPS Overlay", &m_showFPSOverlay, m_FPSOverlayWindownFlags))
	{
		ImGui::Text("FPS Overlay");
		ImGui::Separator();
		ImGui::Text("FPS:%f", m_fps);
	}
	ImGui::End();


	// Rendering
	ImGui::Render();
	SDL_RenderSetScale(Renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
	SDL_SetRenderDrawColor(Renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
	//SDL_RenderClear(Renderer);
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), Renderer);
}

void Game::Render(float deltaTime)
{


	//m_quadTree->Render(m_renderer);
	SDL_SetRenderDrawColor(Renderer, 31, 31, 31, 255);
	SDL_RenderClear(Renderer);

	m_quadTreev2->Render(Renderer);
	
	CurrentScene->Render();

	m_healthBar->Render();

	if (m_showFPSOverlay)
	{
		RenderImGUI();
	}
	
	SDL_RenderPresent(Renderer);
}


void Game::Clean()
{
	// Cleanup
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	Mix_HaltMusic();
	Mix_FreeMusic(music);

	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(Renderer);
	SDL_Quit();
	std::cout << "Cleaned and quit..." << std::endl;
}

bool Game::IsRunning()
{
	return m_isRunning;
}