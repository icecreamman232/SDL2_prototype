#include "PowerUpManager.h"
#include <random>
#include "PowerUpEventDispatcher.h"


void PowerUpManager::Initialize()
{
	PowerUpEventDispatcher::Attach(this);
}

PowerUpManager::~PowerUpManager()
{
	PowerUpEventDispatcher::Detach(this);
}

void PowerUpManager::AssignPlayer(SpaceShip* player)
{
	m_player = player;
}

PowerUpType PowerUpManager::GetRandomPowerUp()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(1, PowerUpType::COUNT - 1);
	return (PowerUpType)dist(gen);
}

void PowerUpManager::ApplyPowerUp()
{
	for(auto powerup : m_appliedContainer)
	{
		powerup.second->Apply(m_player);
	}
}

void PowerUpManager::OnTriggerEvent(const PowerUpEvent& eventType)
{
	if (m_player == nullptr) return;
	AddPowerUp(eventType.PowerUpType);
}

void PowerUpManager::AddPowerUp(PowerUpType type)
{
	//Check if we have this power up available
	if (m_powerUpContainer.count(type) > 0)
	{
		//Add it to applied container
		m_appliedContainer[type] = m_powerUpContainer[type];
		//Remove it from availble container
		m_powerUpContainer.erase(type);
	}
}
