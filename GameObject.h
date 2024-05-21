#pragma once
#include <vector>
#include <SDL.h>

#include "Math/Vector2.h"
#include "Global.h"
#include "LayerManager.h"
#include "Sprite.h"

class Collider;

class GameObject
{
public:
	GameObject();
	GameObject(const char* name,TEXTURE_ID textureID, int initX, int initY,int width, int height, int order = 0);
	GameObject(const char* name, TEXTURE_ID textureID, int width, int height, int order = 0);
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
	inline Sprite* GetSprite() { return m_sprite; };

protected:
	bool m_isActive;
	const char* m_name;
	double m_angle;
	Vector2 m_pos;
	Collider* m_collider;

	Sprite* m_sprite;
};

