#pragma once
#include <unordered_map>
#include "ISubscriber.h"
#include "PowerUpBase.h"
#include "SpaceShip.h"
#include "MyEvent.h"
#include "Global.h"
#include <map>

class PowerUpManager : public ISubscriber<PowerUpEvent>
{
public:
	void Initialize();
	~PowerUpManager();
	void AssignPlayer(SpaceShip* player);
	/// <summary>
	/// Get random available power up from the pool. 
	/// The chosen one should not be applied before
	/// </summary>
	/// <returns></returns>
	PowerUpType GetRandomPowerUp();
	void ApplyPowerUp();
	void OnTriggerEvent(const PowerUpEvent& eventType) override;

private:
	/// <summary>
	/// Apply powerup to player
	/// </summary>
	/// <param name="type"></param>
	void AddPowerUp(PowerUpType type);

	std::map<PowerUpType, PowerUpBase*>  m_appliedContainer;
	std::unordered_map<PowerUpType, PowerUpBase*> m_powerUpContainer;

	SpaceShip* m_player;
};

