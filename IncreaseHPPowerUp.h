#pragma once
#include "Global.h"
#include "SpaceShip.h"
#include "PowerUpBase.h"

class IncreaseHPPowerUp : public PowerUpBase
{
public:
	void Apply(SpaceShip* player) override;
	void AssignPlayer(SpaceShip* player);
private:
	float m_percentIncrease;
	SpaceShip* m_playerRef;
};

