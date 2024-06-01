#pragma once

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