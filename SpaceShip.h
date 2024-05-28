#pragma once
#include "GameObject.h"
#include "Health.h"
#include "Input.h"
#include "Weapon.h"
#include "ISubscriber.h"
#include "MyEvent.h"


class SpaceShip : public GameObject, public ISubscriber<EnemyHealthEvent>
{
public:
	SpaceShip(const char* name,TEXTURE_ID textureID, int initX, int initY,int width, int height, int order=0);
	void Update(float deltaTime) override;

	void OnTriggerEvent(const EnemyHealthEvent& eventType) override;

	void SetDirectionX(float);
	void SetDirectionY(float);
	void TakeDamage(int damage);
	float GetPercentHealth();

private:
	float m_invulnerableDuration;
	float m_flickerTimer; //use for calculating flickering sprite color duration
	float m_flickerInterval;

	float m_moveSpeed;
	Vector2 m_direction;
	Health m_health;
	Weapon* m_primaryWeapon;

	void UpdateInput();
	void UpdateMovement(float deltaTime);
};

