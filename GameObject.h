#pragma once
#include <SDL.h>
#include "TextureLoader.h"
#include "Math/Vector2.h"

class GameObject
{
public:
	GameObject(const char* texturePath, SDL_Renderer* renderer, int initX, int initY);
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void SetPosition(int x, int y);
	virtual void SetRotation(double angle);
	virtual void LookAt(int x, int y);

protected:
	double m_angle;
	Vector2 m_pos;
	//float m_posX;
	//float m_posY;
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	SDL_Rect m_srcRect;
	SDL_FRect m_destRect;

};

