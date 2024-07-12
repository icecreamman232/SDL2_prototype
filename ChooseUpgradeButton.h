#pragma once
#include "Selectable.h"
#include "UIImage.h"
#include "BMTextRenderer.h"
#include "Global.h"

class ChooseUpgradeButton : public UIImage, public Selectable
{
public:
	void Init(std::string name, Render::TEXTURE_ID textureID, int x, int y, int width, int height, int spriteFrame = 0) override;
	void Update() override;
	void OnMouseLeftClick() override;
	void SetSelectedCard(PowerUpType type);
private:

	void ChooseUpgrade();

	BMTextRenderer m_btnText;
	//Index of the upgrade card that player selects
	PowerUpType m_cardSelectedValue = None;
};

