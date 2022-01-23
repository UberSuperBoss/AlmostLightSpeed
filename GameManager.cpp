#include "GameManager.hpp"

SDL_Event GameManager::event;
EntityManager* GameManager::entityManager;

bool GameManager::running;
double GameManager::screenSizeMultiplier = 0;
GameStatus GameManager::gameStatus;

GameManager::GameManager()
{
	std::cout << "Game Initiation Began" << std::endl;

	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		std::cout << "Init Everything" << std::endl;

		SDL_DisplayMode dm;
		SDL_GetDesktopDisplayMode(0, &dm);

		if ((dm.w / dm.h) >= (1 + (7 / 9)))
		{
			//Width is larger than height
			screenSizeMultiplier = dm.w / 960.0;
		}
		else 
		{
			//Height is larger than width
			screenSizeMultiplier = dm.h / 540.0;
		}

		//SDL_CreateWindowAndRenderer(960, 540, 0, &window, &Renderer::renderer);

		window = SDL_CreateWindow("AlmostLightSpeed", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, static_cast<int>(960.0 * screenSizeMultiplier), static_cast<int>(540.0 * screenSizeMultiplier), SDL_WINDOW_FULLSCREEN);

		Renderer::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (Renderer::renderer)
		{
			// Change screen colour
			SDL_SetRenderDrawColor(Renderer::renderer, 255, 255, 255, 255);
		}
		

		SDL_ShowCursor(SDL_DISABLE);

		this->running = true;
	}	
	else
	{
		std::cout << "Game Initialization Failed" << std::endl;
	}

	if (TTF_Init() == -1) {
		std::cout << "Could not initailize SDL2_ttf, error: " << TTF_GetError() << std::endl;
	}

	std::srand(std::time(nullptr)); // use current time as seed for random generator
	
	Renderer::init(screenSizeMultiplier);
	Mixer::init();

	entityManager = new EntityManager(screenSizeMultiplier);

	gameStatus = GameStatus::StartMenu;

	Mixer::playSong(Song::TitleScreen);

	std::cout << "Game Initiated" << std::endl;

}

void GameManager::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		this->running = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			this->running = false;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:

		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

		if (gameStatus == GameStatus::StartMenu)
		{
			/*
			Mixer::playSoundEffect(SoundEffect::Start);
			*/
			gameStatus = GameStatus::Playing;

			Mix_HaltMusic();
			Mixer::playSong(Song::Main);
		}
		else if (gameStatus == GameStatus::Dead)
		{
			EntityManager::speed = 1000;
			gameStatus = GameStatus::Playing;
			/*
			Mix_HaltChannel(-1);
			Mixer::playSoundEffect(SoundEffect::Start);
			*/

			Mix_HaltMusic();
			Mixer::playSong(Song::Main);
		}
	default:
		break;
	}
}

void GameManager::render()
{
	SDL_RenderClear(Renderer::renderer);

	const std::string speedText = std::string() + "Speed: " + std::to_string(((double)entityManager->speed) / 10000) + "c";

	switch (gameStatus)
	{
	case GameStatus::StartMenu:
		Renderer::render(TextureType::Background);
		Renderer::render(TextureType::Title);
		break;
	case GameStatus::Playing:
		Renderer::render(TextureType::Background);
		Renderer::renderText(speedText, 5, 5, screenSizeMultiplier);
		entityManager->render();
		break;
	case GameStatus::Dead:
		Renderer::render(TextureType::Dead);
		Renderer::renderText(speedText, 5, 5, screenSizeMultiplier, {0,0,0});
		break;
	case GameStatus::Pause:
		break;
	}

	SDL_RenderPresent(Renderer::renderer);
}

void GameManager::clean()
{
	Renderer::clean();

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(Renderer::renderer);
	SDL_Quit();
}
