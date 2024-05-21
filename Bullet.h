#pragma once
#include <SDL.h>
#include "AssetManager.h"
#include "Math/Vector2.h"
#include "GameObject.h"

class Weapon;

class Bullet : public GameObject
{
public:
	Bullet();
	void Initialize(Weapon* weaponOwner,const char* name, TEXTURE_ID textureID,
		int initX, int initY, int width, int height);
	void Update(float deltaTime) override;
	void Render();
	void SetAngle(float angle);
	void SetDirection(Vector2 direction);
private:
	bool m_isInitialized;
	Weapon* m_weapon;
	float m_moveSpeed;
	Vector2 m_direction;
	float m_test;

	void Destroy();
};

