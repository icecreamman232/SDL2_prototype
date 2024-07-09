#include "UpgradeCard.h"
#include "TweenManager.h"
#include "Logger.h"
#include "Game.h"

UpgradeCard::~UpgradeCard()
{
	m_state = nullptr;
	m_chooseUpgradeBtn = nullptr;
}

void UpgradeCard::Init(Render::TEXTURE_ID textureID, int x, int y, int width, int height, int spriteFrame)
{
	InitSelectable(x, y, width, height);
	UIImage::Init(textureID, x, y, width, height, spriteFrame);
}

void UpgradeCard::AssignChooseUpgradeButton(ChooseUpgradeButton* buttonRef)
{
	m_chooseUpgradeBtn = buttonRef;
}

void UpgradeCard::SetUpgradeCardIndex(Uint8 index)
{
	m_cardIndex = index;
}

void UpgradeCard::Update()
{
	if (m_state == nullptr) return;
	m_icon.SetPosition(m_pos.x + m_width/2 - m_icon.GetWidth()/2, m_pos.y + m_topPadding);
	m_icon.Update();

	UpdateSelectable();
	UIImage::Update();
}

void UpgradeCard::AssignCardValue(PowerUpType powerUpType)
{
	m_cardValue = powerUpType;
	auto textureID = Render::TEXTURE_ID::POWERUP_ICON;
	auto width = 200;
	auto height = width;
	auto x = m_pos.x + m_width/2 - width/2;
	auto y = m_pos.y + m_topPadding;
	
	//Base on which powerup type we set frame for sprite to get properly icon
	switch (powerUpType)
	{
		case PowerUpType::Increase_HP:
			m_icon.Init(textureID, x, y, width, height, 0);
			break;
		case PowerUpType::Increase_Damage:
			m_icon.Init(textureID, x, y, width, height, 0);
			break;
		case PowerUpType::Increase_MAX_HP:
			m_icon.Init(textureID, x, y, width, height, 0);
			break;
		case PowerUpType::Increase_MoveSpeed:
			m_icon.Init(textureID, x, y, width, height, 0);
			break;
	}
	Game::CurrentScene->Add(&m_icon);
}

void UpgradeCard::AssignEndWaveStateRef(EndWaveState* state)
{
	m_state = state;
}

void UpgradeCard::OnSelect()
{
	TweenManager::Instance().CreateTween(Tween::TweenEase::OUT_QUINT,
		this, m_pos.x, m_originalY - 20, 0.3f);
	m_chooseUpgradeBtn->SetSelectedCard(m_cardIndex);
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

void UpgradeCard::OnFinishTween()
{
	m_icon.SetPosition(m_pos.x, m_pos.y);
}

