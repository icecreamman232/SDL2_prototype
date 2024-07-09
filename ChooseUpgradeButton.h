#pragma once
#include "Selectable.h"
#include "UIImage.h"
#include "BMTextRenderer.h"

class ChooseUpgradeButton : public UIImage, public Selectable
{
public:
	void Init(Render::TEXTURE_ID textureID, int x, int y, int width, int height, int spriteFrame = 0) override;
	void Update() override;
	void OnMouseLeftClick() override;
	void SetSelectedCard(Uint8 index);
private:

	void ChooseUpgrade();

	BMTextRenderer m_btnText;
	//Index of the upgrade card that player selects
	Uint8 m_cardSelectedValue = -1;
};

