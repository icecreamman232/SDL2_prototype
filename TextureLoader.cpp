#include "TextureLoader.h"

SDL_Texture* TextureLoader::LoadTexture(const char* path, SDL_Renderer* renderer)
{
	SDL_Surface* surface = IMG_Load(path);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return tex;
}