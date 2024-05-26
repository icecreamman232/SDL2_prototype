#pragma once
#include "GameObject.h"
#include <random>
#include "Health.h"
#include "Animation.h"
#include "SDL_mixer.h"

class Slime : public GameObject
{
public:
	Slime(const char* name, TEXTURE_ID textureID ,
		int initX, int initY, int width, int height,int order = 0);
	~Slime() override;
	void Update(float deltaTime) override;
	void TakeDamage(int damage);
	int GetDamage();

	inline bool IsDead() { return m_health->GetCurrentHealth() <= 0; };
private:

	void GetNextDirection(Vector2& direction);
	void UpdateMovement(float deltaTime);

	int m_minDamage;
	int m_maxDamage;

	float m_moveSpeed;
	Vector2 m_direction;
	Health* m_health;
	bool m_canMove;

	Animation* m_idleAnim;
	Animation* m_deadAnim;

	Mix_Chunk* m_deadSFX;
};

