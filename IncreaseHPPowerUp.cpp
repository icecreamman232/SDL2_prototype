#include "IncreaseHPPowerUp.h"
#include "Logger.h"

void IncreaseHPPowerUp::Apply()
{
	if (m_playerRef == nullptr)
	{
		DebugLog("Player Ref is NULL");
	}
	auto curMaxHealth = m_playerRef->GetHealth().GetMaxHealth();
	curMaxHealth = curMaxHealth * (m_percentIncrease / 100.0f + 1.0f);
	m_playerRef->SetMaxHealth(curMaxHealth);
}

void IncreaseHPPowerUp::AssignPlayer(SpaceShip* player)
{
	m_playerRef = player;
}
