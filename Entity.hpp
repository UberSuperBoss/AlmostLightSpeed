#pragma once
#include <SDL.h>
#include "Renderer.hpp"

#include <iostream>

class Entity {
public:
	Entity(EntityType type);
	~Entity();
	void render();
	void update();

	TextureType textureType;
	EntityType entityType;
	SDL_Rect destR;};