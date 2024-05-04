#pragma once
#include <SDL.h>
#include "TextureLoader.h"

class GameObject
{
public:
	GameObject(const char* texturePath, SDL_Renderer* renderer, int initX, int initY);
	void Update();
	void Render();


private:
	int m_posX;
	int m_posY;
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	SDL_Rect m_srcRect, m_destRect;

};

