#include "PowerUpBase.h"

void PowerUpBase::Initialize(PowerUpType type)
{
	m_type = type;
}

void PowerUpBase::Apply(SpaceShip* player)
{
}

PowerUpType PowerUpBase::GetPU_Type()
{
	return m_type;
}
