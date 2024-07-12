#include "IncreaseHPPowerUp.h"
#include "Logger.h"

void IncreaseHPPowerUp::Apply(SpaceShip* player)
{
	if (player == nullptr)
	{
		DebugLog("Player Ref is NULL");
	}
	auto curMaxHealth = player->GetHealth().GetMaxHealth();
	curMaxHealth = curMaxHealth * (m_percentIncrease / 100.0f + 1.0f);
	player->SetMaxHealth(curMaxHealth);
}

void IncreaseHPPowerUp::AssignPlayer(SpaceShip* player)
{
	m_playerRef = player;
}
