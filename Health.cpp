#include "Health.h"
#include "Timer.h"

void Health::Initialize(int maxHealth, float invulnerableDuration)
{
	m_maxHealth = maxHealth;
	m_curHealth = m_maxHealth;
	m_invulnerableDuration = invulnerableDuration;
}

void Health::TakeDamage(int damage)
{
	if (m_isInvulnerable) return;
	m_curHealth -= damage;
	m_isInvulnerable = true;
	Timer* invulnerableTimer = new Timer(m_invulnerableDuration, std::bind(&Health::AfterInvulerableCallback, this));
}

int Health::GetCurrentHealth()
{
	return m_curHealth;
}

int Health::GetMaxHealth()
{
	return m_maxHealth;
}


void Health::AfterInvulerableCallback()
{
	m_isInvulnerable = false;
}
