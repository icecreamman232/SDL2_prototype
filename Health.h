#pragma once
#include <SDL.h>
class Health
{
public:
	void Initialize(int maxHealth, float invulnerableDuration);
	void TakeDamage(int damage);

	int GetCurrentHealth();
	int GetMaxHealth();
	void SetMaxHealth(int maxHealth);
	void AfterInvulerableCallback(); //Can we set it to be private ?!
	inline bool IsInvulernable() {return m_isInvulnerable; };

protected:
	bool m_isInvulnerable;
	float m_invulnerableDuration;
	int m_maxHealth;
	int m_curHealth;
};

