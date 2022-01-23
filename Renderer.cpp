#include "Renderer.hpp"

SDL_Renderer* Renderer::renderer = nullptr;
TTF_Font* Renderer::font = nullptr;
SDL_Texture* Renderer::textures[14] = {nullptr};

double Renderer::screenSizeMultiplier = 0;

SDL_Texture* Renderer::loadTexture(const char* textureName)
{
	return IMG_LoadTexture(renderer, textureName);
}

void Renderer::init(double multiplier)
{

	screenSizeMultiplier = multiplier;

	Renderer::textures[0] = loadTexture("./assets/gfx/background.png");
	Renderer::textures[1] = loadTexture("./assets/gfx/starship.png");
	Renderer::textures[2] = loadTexture("./assets/gfx/asteroid1.png");
	Renderer::textures[3] = loadTexture("./assets/gfx/asteroid2.png");

	Renderer::textures[4] = loadTexture("./assets/gfx/exhaust/1.png");
	Renderer::textures[5] = loadTexture("./assets/gfx/exhaust/2.png");
	Renderer::textures[6] = loadTexture("./assets/gfx/exhaust/3.png");
	Renderer::textures[7] = loadTexture("./assets/gfx/exhaust/4.png");
	Renderer::textures[8] = loadTexture("./assets/gfx/exhaust/turbo1.png");
	Renderer::textures[9] = loadTexture("./assets/gfx/exhaust/turbo2.png");
	Renderer::textures[10] = loadTexture("./assets/gfx/exhaust/turbo3.png");
	Renderer::textures[11] = loadTexture("./assets/gfx/exhaust/turbo4.png");

	Renderer::textures[12] = loadTexture("./assets/gfx/title.png");
	Renderer::textures[13] = loadTexture("./assets/gfx/dead.png");

	Renderer::font = TTF_OpenFont("./assets/fonts/font.ttf", 32);

	std::cout << "load images" << std::endl;
}

void Renderer::clean()
{
	for (SDL_Texture* texture : textures) SDL_DestroyTexture(texture);

	TTF_CloseFont(font);
}

void Renderer::render(TextureType textureType, SDL_Rect* destR)
{	
	SDL_RenderCopy(renderer, textures[static_cast<int>(textureType)], NULL, destR);
}

void Renderer::render(TextureType textureType)
{
	SDL_Rect fullscreenRect = { 0,0, static_cast<int>(960.0 * screenSizeMultiplier), static_cast<int>(540.0 * screenSizeMultiplier) };
	SDL_RenderCopy(renderer, textures[static_cast<int>(textureType)], NULL, &fullscreenRect);
}

void Renderer::renderFlip(TextureType textureType, SDL_Rect* destR, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, textures[static_cast<int>(textureType)], NULL, destR, NULL, NULL, flip);
}

void Renderer::setSize(TextureType textureType, SDL_Rect* destR)
{
	int index = static_cast<int>(textureType);
	SDL_QueryTexture(Renderer::textures[index], NULL, NULL, &destR->w, &destR->h);

	//Size of Image
	destR->h *= screenSizeMultiplier; destR->w *= screenSizeMultiplier;
}

void Renderer::clearScreen()
{
	SDL_RenderClear(renderer);
	SDL_RenderPresent(Renderer::renderer);
}

void Renderer::renderText(std::string text, int x, int y, double sizeMultiplier)
{
	SDL_Rect destR = { x, y, 0, 0 };

	TTF_SizeText(font, text.c_str(), &destR.w, &destR.h);

	destR.w *= sizeMultiplier;
	destR.h *= sizeMultiplier;

	SDL_Surface* surfaceText = TTF_RenderText_Solid(Renderer::font, text.c_str(), { 255,255,255 });
	SDL_Texture* textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);
	SDL_FreeSurface(surfaceText);

	//SDL_SetTextureAlphaMod(textureText, 200);

	SDL_RenderCopy(renderer, textureText, NULL, &destR);

	SDL_DestroyTexture(textureText);
}

void Renderer::renderText(std::string text, int x, int y, double sizeMultiplier, SDL_Color color)
{
	SDL_Rect destR = { x, y, 0, 0 };

	TTF_SizeText(font, text.c_str(), &destR.w, &destR.h);

	destR.w *= sizeMultiplier;
	destR.h *= sizeMultiplier;

	SDL_Surface* surfaceText = TTF_RenderText_Solid(Renderer::font, text.c_str(), color);
	SDL_Texture* textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);
	SDL_FreeSurface(surfaceText);

	//SDL_SetTextureAlphaMod(textureText, 200);

	SDL_RenderCopy(renderer, textureText, NULL, &destR);

	SDL_DestroyTexture(textureText);
}