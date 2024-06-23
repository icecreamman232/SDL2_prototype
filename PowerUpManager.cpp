#include "PowerUpManager.h"
#include <random>

void PowerUpManager::Initialize()
{
	

}

PowerUpType PowerUpManager::GetRandomPowerUp()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, PowerUpType::COUNT - 1);
	return (PowerUpType)dist(gen);
}

void PowerUpManager::AddPowerUp(PowerUpBase* powerup)
{
	
}
