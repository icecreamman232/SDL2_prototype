#pragma once
#include "Global.h"

class PowerUpBase
{
public:
	virtual void Initialize(PowerUpType type);
	virtual void Apply();
	virtual PowerUpType GetPU_Type();
protected:
	PowerUpType m_type;
};

