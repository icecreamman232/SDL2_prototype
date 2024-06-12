#include "UpgradeCard.h"
#include "TweenManager.h"
#include <iostream>

UpgradeCard::~UpgradeCard()
{
	m_state = nullptr;
}

void UpgradeCard::AssignEndWaveStateRef(EndWaveState* state)
{
	m_state = state;
}

void UpgradeCard::OnMouseEnter()
{
	TweenManager::Instance().CreateTween(Tween::TweenEase::OUT_QUINT,
		this, m_pos.x, m_originalY - 20 , 0.5f);
}

void UpgradeCard::OnMouseExit()
{
	TweenManager::Instance().CreateTween(Tween::TweenEase::OUT_QUINT,
		this, m_pos.x, m_originalY + 20, 0.5f);
}

void UpgradeCard::SetOriginal_Y(float value)
{
	m_originalY = value;
}
