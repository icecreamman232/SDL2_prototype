#pragma once
#include "Global.h"
#include "Math/Vector2.h"

struct EnemyHealthEvent
{
	bool IsDead;
	Vector2 DeadPosition;
};

struct XPEvent
{
	int XPGain;
};

struct LevelUpEvent
{
	int CurrentLv;
	int PreviousLv;
};

struct CoinCollectEvent
{
	int CoinValue;
};

struct PickUpgradeEvent
{
	PowerUpType PowerUpType;
};

struct PowerUpEvent
{
	PowerUpType PowerUpType;
};

struct PlayerStateEvent
{
	General::PlayerState PlayerState;
};