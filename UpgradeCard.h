#pragma once
#include "UIImage.h"
#include "Global.h"
class EndWaveState;

class UpgradeCard : public UIImage
{
public:
	~UpgradeCard();
	void Update() override;
	void AssignCardValue(PowerUpType value);
	void AssignEndWaveStateRef(EndWaveState* state);
	void OnMouseEnter() override;
	void OnMouseExit() override;
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

	const float m_topPadding = 30;
};

