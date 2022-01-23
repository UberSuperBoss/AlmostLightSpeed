#pragma once
#include "Renderer.hpp"
#include "Mixer.hpp"
#include "EntityManager.hpp"
#include <iostream>
#include <SDL.h>

class GameManager
{
public:
	GameManager();

	void handleEvents();
	void render();
	void clean();

	static bool running;	
	static GameStatus gameStatus;

	static SDL_Event event;
	static EntityManager* entityManager;

	static double screenSizeMultiplier;
private:
	SDL_Window* window;
};