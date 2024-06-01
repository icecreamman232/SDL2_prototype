#include "Game.h"
#include "SDL_image.h"
#include "GameObject.h"
#include "Input.h"


int Game::ScreenWidth = 0;
int Game::ScreenHeight = 0;
SDL_Renderer* Game::Renderer = nullptr;
Scene* Game::CurrentScene = nullptr;
QuadTreev2* Game::m_quadTreev2 = nullptr;
float Game::DeltaTime = 0;

using namespace General;

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

Game::Game()
{
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
		//Nearest pixel sampling setting
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
		std::cout << "Initialized..." << std::endl;
		SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
		m_window = SDL_CreateWindow("Prototype", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, g_WindowSettings.Width, g_WindowSettings.Height, window_flags);
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


	DeltaTime = 1.0 /60.0;

	music = Mix_LoadMUS("Asset/Music/DaniStob-OverdriveSunset-Loop.wav");

	AssetManager::Instance().Initialize();
	CurrentScene = new Scene();


	m_quadTreev2 = new QuadTreev2(SDL_FRect{ 0.0,0.0,static_cast<float>(ScreenWidth) ,static_cast<float>(ScreenHeight) }, 0, 0);

	m_gameStateManager.Initialize();

	//Mix_PlayMusic(music, -1);
	Mix_FadeInMusic(music, -1, 1500);
	/*while (Mix_FadingMusic() == MIX_FADING_IN)
	{
		SDL_Delay(30);
	}*/
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
	DeltaTime = deltaTime;

	m_quadTreev2 = new QuadTreev2(SDL_FRect{ 0.0,0.0,static_cast<float>(ScreenWidth) ,static_cast<float>(ScreenHeight) }, 0, 0);

	m_gameStateManager.Update(deltaTime);

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

	m_gameStateManager.Render();

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