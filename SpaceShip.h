#pragma once
#include "SDL_mixer.h"
#include "GameObject.h"
#include "Health.h"
#include "Input.h"
#include "Weapon.h"
#include "ISubscriber.h"
#include "MyEvent.h"
#include "ExpController.h"


class SpaceShip : public GameObject, 
	public ISubscriber<XPEvent>
{
public:
	SpaceShip(const char* name,TEXTURE_ID textureID, float initX, float initY,int width, int height, int order=0);
	~SpaceShip() override;
	void Update(float deltaTime) override;

	void OnTriggerEvent(const XPEvent& eventType) override;

	void SetDirectionX(float);
	void SetDirectionY(float);
	void TakeDamage(int damage);
	float GetPercentHealth();

	Health& GetHealth();
	void SetMaxHealth(int newMaxHP);

	inline ExpController XPController() { return m_xpController; };

private:
	void UpdateInput();
	void UpdateMovement(float deltaTime);

	float m_invulnerableDuration;
	float m_flickerTimer; //use for calculating flickering sprite color duration
	float m_flickerInterval;

	float m_moveSpeed;
	Vector2 m_direction;
	Health m_health;
	Weapon* m_primaryWeapon;

	//====EXP===//
	ExpController m_xpController;

	//===SFX===//
	Mix_Chunk* m_levelUpSFX;
};

