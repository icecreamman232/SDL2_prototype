#include "ChooseUpgradeButton.h"
#include "Logger.h"
#include "Game.h"
#include "PowerUpEventDispatcher.h"

void ChooseUpgradeButton::Init(std::string name, Render::TEXTURE_ID textureID, int x, int y, int width, int height, int spriteFrame)
{
	InitSelectable(x, y, width, height);
	UIImage::Init(name, textureID, x, y, width, height, spriteFrame);

	m_btnText.Initialize(Render::TEXTURE_ID::BM_FONT_PIXEL, 
		"CHOOSE", Render::Pivot::CENTER, x + 80, y+15);
	m_btnText.SetSpacing(14);
	m_btnText.SetSize(24);

	Game::CurrentScene->Add(this);
	Game::CurrentScene->Add(&m_btnText);
}

void ChooseUpgradeButton::Update()
{
	UpdateSelectable();
	m_btnText.Update();
}

void ChooseUpgradeButton::OnMouseLeftClick()
{
	if (m_cardSelectedValue < 0) return;
	ChooseUpgrade();
}

void ChooseUpgradeButton::SetSelectedCard(PowerUpType type)
{
	m_cardSelectedValue = type;
}

void ChooseUpgradeButton::ChooseUpgrade()
{
	if (m_cardSelectedValue < 0) return;

	PowerUpEventDispatcher::Trigger(PowerUpEvent{ m_cardSelectedValue });
}
