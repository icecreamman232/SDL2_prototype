#pragma once
#include "Selectable.h"
#include "UIImage.h"
#include "BMTextRenderer.h"
#include "Global.h"
#include <functional>

class ChooseUpgradeButton : public UIImage, public Selectable
{
public:
	void Init(std::string name, Render::TEXTURE_ID textureID, int x, int y, int width, int height, int spriteFrame = 0) override;
	void CleanUp();
	void Update() override;
	void OnMouseLeftClick() override;
	void SetSelectedCard(PowerUpType type);

	using CallbackFunction = std::function<void()>;
	void SetCallBack(CallbackFunction callback);
	
private:
	bool m_shouldUpdate = false;

	void TriggerCallBack();
	void ChooseUpgrade();

	CallbackFunction m_callback;
	BMTextRenderer m_btnText;
	//Index of the upgrade card that player selects
	PowerUpType m_cardSelectedValue = None;
};

