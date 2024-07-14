#pragma once
#include "UIImage.h"
#include "Selectable.h"
#include "ChooseUpgradeButton.h"
#include "Global.h"
class EndWaveState;

class UpgradeCard : public UIImage, public Selectable
{
public:
	~UpgradeCard();
	void CleanUp();
	void Init(std::string name, Render::TEXTURE_ID textureID, int x, int y, int width, int height, int spriteFrame = 0) override;
	void AssignChooseUpgradeButton(ChooseUpgradeButton* buttonRef);
	void Update() override;
	void AssignCardValue(PowerUpType value);
	void AssignEndWaveStateRef(EndWaveState* state);
	void OnSelect() override;
	void OnDeselect() override;
	void SetOriginal_Y(float value);
	void OnFinishTween();
private:
	EndWaveState* m_state;
	float m_originalY;
	//Represent for which powerup index that got random in game state
	PowerUpType m_cardValue;
	UIImage m_icon;
	ChooseUpgradeButton* m_chooseUpgradeBtn;

	const float m_topPadding = 30;
};

