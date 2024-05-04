#pragma once
#include <SDL.h>
#include <SDL_image.h>

class TextureLoader
{
public:
	static SDL_Texture* LoadTexture(const char* path, SDL_Renderer* renderer);

};

