#pragma once
#include <SDL.h>
#include "TextureLoader.h"

class GameObject
{
public:
	GameObject(const char* texturePath, SDL_Renderer* renderer, int initX, int initY);
	void Update();
	void Render();
	void SetPosition(int x, int y);
	void SetRotation(double angle);
	void LookAt(int x, int y);

private:
	double m_angle;
	int m_posX;
	int m_posY;
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	SDL_Rect m_srcRect, m_destRect;

};

