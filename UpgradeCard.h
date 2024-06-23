#pragma once
#include "UIImage.h"
#include "Global.h"
class EndWaveState;

class UpgradeCard : public UIImage
{
public:
	~UpgradeCard();
	void AssignCardValue(PowerUpType value);
	void AssignEndWaveStateRef(EndWaveState* state);
	void OnMouseEnter() override;
	void OnMouseExit() override;
	void OnSelect() override;
	void OnDeselect() override;
	void SetOriginal_Y(float value);
private:
	EndWaveState* m_state;
	float m_originalY;
	//Represent for which powerup index that got random in game state
	PowerUpType m_cardValue;
};

