#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "Enums.h"

class Renderer
{
public:
	static void init(double multiplier);
	static void	clean();
		
	static void render(TextureType textureType, SDL_Rect* destR);
	static void render(TextureType textureType);
	static void renderFlip(TextureType textureType, SDL_Rect* destR, SDL_RendererFlip flip);

	static void setSize(TextureType textureType, SDL_Rect* destR);

	static void clearScreen();

	static void renderText(std::string text, int x, int y, double sizeMultiplier);

	static void renderText(std::string text, int x, int y, double sizeMultiplier, SDL_Color color);
		
	static double screenSizeMultiplier;

	static SDL_Texture* textures[14];
	static TTF_Font* font;
	static SDL_Renderer* renderer;
private:
	static SDL_Texture* loadTexture(const char* textureName);
};
