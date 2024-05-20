#pragma once
#include <vector>
#include <SDL.h>

#include "Math/Vector2.h"
#include "Global.h"
#include "LayerManager.h"

class Collider;

class GameObject
{
public:
	GameObject(const char* name, SDL_Texture* texture, int initX, int initY,int width, int height);
	GameObject(const char* name, SDL_Texture* texture, int width, int height);
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void SetPosition(int x, int y);
	virtual void SetRotation(double angle);
	virtual void LookAt(int x, int y);
	virtual bool IsCollideWith(GameObject* other);
	virtual void SetLayer(Layer layer);
	const SDL_FRect Rect();

	inline Vector2 GetPosition() { return m_pos; };
	inline const char* GetName() { return m_name; };
	inline void SetActive(bool isActive) { m_isActive = isActive; };

protected:
	bool m_isActive;
	const char* m_name;
	double m_angle;
	Vector2 m_pos;
	Collider* m_collider;
	SDL_Texture* m_texture;
	SDL_Rect m_srcRect;
	SDL_FRect m_destRect;
};

