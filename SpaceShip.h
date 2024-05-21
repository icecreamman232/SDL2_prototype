#pragma once
#include "GameObject.h"
#include "Health.h"
#include "Input.h"
#include "Weapon.h"

class SpaceShip : public GameObject
{
public:
	SpaceShip(const char* name,TEXTURE_ID textureID, int initX, int initY,int width, int height, int order=0);
	void Update(float deltaTime) override;

	void SetDirectionX(float);
	void SetDirectionY(float);
	void TakeDamage();
	float GetPercentHealth();

private:
	float m_moveSpeed;
	Vector2 m_direction;
	Health m_health;
	Weapon* m_primaryWeapon;

	void UpdateInput();
	void UpdateMovement(float deltaTime);
};

