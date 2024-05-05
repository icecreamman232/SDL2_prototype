#pragma once
#include <SDL.h>
#include "TextureLoader.h"
#include "Math/Vector2.h"
class Collider;

class GameObject
{
public:
	GameObject(const char* name, const char* texturePath, SDL_Renderer* renderer, int initX, int initY,int width, int height);
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void SetPosition(int x, int y);
	virtual void SetRotation(double angle);
	virtual void LookAt(int x, int y);
	virtual bool IsCollideWith(GameObject* other);
	const SDL_FRect Rect();
protected:
	const char* m_name;
	double m_angle;
	Vector2 m_pos;
	Collider* m_collider;
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	SDL_Rect m_srcRect;
	SDL_FRect m_destRect;
};

