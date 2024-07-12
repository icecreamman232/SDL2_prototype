#pragma once
#include "Global.h"

class SpaceShip;

class PowerUpBase
{
public:
	virtual void Initialize(PowerUpType type);
	virtual void Apply(SpaceShip* player);
	virtual PowerUpType GetPU_Type();
protected:
	PowerUpType m_type;
};

