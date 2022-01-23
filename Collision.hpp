#pragma once
#include <SDL.h>
#include <iostream>

class Collision
{
public:
	static bool isTouching(const SDL_Rect& recA, const SDL_Rect& recB);
};