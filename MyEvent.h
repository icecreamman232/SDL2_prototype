#pragma once

struct EnemyHealthEvent
{
	bool IsDead;
	int CurrentHealth;
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