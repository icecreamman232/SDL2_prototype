#pragma once
#include <unordered_map>
#include "PowerUpBase.h"
#include "Global.h"

class PowerUpManager
{
public:
	void Initialize();
	PowerUpType GetRandomPowerUp();
	void AddPowerUp(PowerUpBase* powerup);

private:
	std::unordered_map<PowerUpType, PowerUpBase*> m_powerUpContainer;

};

