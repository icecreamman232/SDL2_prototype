#pragma once
#include <SDL.h>
class Health
{
public:
	void Initialize(int maxHealth, float invulnerableDuration);
	void TakeDamage(int damage);

	int GetCurrentHealth();
	int GetMaxHealth();
	void AfterInvulerableCallback(); //Can we set it to be private ?!

protected:
	bool m_isInvulnerable;
	float m_invulnerableDuration;
	int m_maxHealth;
	int m_curHealth;
};

