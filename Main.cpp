#include "GameManager.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif


#ifdef __EMSCRIPTEN__
static void loop();
static GameManager* gameManager = new GameManager();

int main(int argc, char* argv[])
{
	GameManager* gameManager = new GameManager();
	emscripten_set_main_loop(loop, 60, true);
	std::cout << "start" << std::endl;
}

void loop()
{
	gameManager->handleEvents();
	gameManager->render();
}

#else

static void capFrameRate(long* then, float* remainder);

int main(int argc, char* argv[])
{
	std::cout << "Program Started" << std::endl;

	GameManager* gameManager = new GameManager();

	long then;
	float remainder;

	then = SDL_GetTicks();

	remainder = 0;

	while (gameManager->running)
	{
		gameManager->handleEvents();
		gameManager->render();

		capFrameRate(&then, &remainder);
	}

	gameManager->clean();

	std::cout << "Program Ended" << std::endl;

	return 0;
}

static void capFrameRate(long* then, float* remainder)
{
	long wait, frameTime;

	wait = 16 + *remainder;

	*remainder -= (int)*remainder;

	frameTime = SDL_GetTicks() - *then;

	wait -= frameTime;

	if (wait < 1)
	{
		wait = 1;
	}

	SDL_Delay(wait);

	*remainder += 0.667;

	*then = SDL_GetTicks();
}
#endif

/*
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	while (gameManager->running)
	{
		frameStart = SDL_GetTicks();

		gameManager->handleEvents();
		gameManager->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	*/

	/*
	Uint32 last_update_ticks = SDL_GetTicks();
	// Event loop:
	while (gameManager->running) {
		// ...
		Uint32 update_ticks = SDL_GetTicks();
		Uint32 ticks_elapsed = update_ticks - last_update_ticks;
		last_update_ticks = update_ticks;

		gameManager->handleEvents();
		gameManager->render();

		//update_world(ticks_elapsed); // Then you can update the position with speed * ticks_elapsed
		// ...
	}
	*/

	/*
	double t = 0.0;
	double dt = 1.0 / 60.0;

	while (gameManager->running)
	{
		gameManager->handleEvents();
		gameManager->render();
		t += dt;
	}
	*/