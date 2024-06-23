#include "UpgradeCard.h"
#include "TweenManager.h"
#include <iostream>
#include "Logger.h"

UpgradeCard::~UpgradeCard()
{
	m_state = nullptr;
}

void UpgradeCard::AssignCardValue(PowerUpType value)
{
	m_cardValue = value;
}

void UpgradeCard::AssignEndWaveStateRef(EndWaveState* state)
{
	m_state = state;
}

void UpgradeCard::OnMouseEnter()
{
	
}

void UpgradeCard::OnMouseExit()
{
	
}

void UpgradeCard::OnSelect()
{
	TweenManager::Instance().CreateTween(Tween::TweenEase::OUT_QUINT,
		this, m_pos.x, m_originalY - 20, 0.3f);
	DebugLog("Select");
}

void UpgradeCard::OnDeselect()
{
	TweenManager::Instance().CreateTween(Tween::TweenEase::OUT_QUINT,
		this, m_pos.x, m_originalY + 20, 0.3f);
}

void UpgradeCard::SetOriginal_Y(float value)
{
	m_originalY = value;
}
