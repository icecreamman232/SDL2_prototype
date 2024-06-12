#pragma once
#include "UIImage.h"
class EndWaveState;

class UpgradeCard : public UIImage
{
public:
	~UpgradeCard();
	void AssignEndWaveStateRef(EndWaveState* state);
	void OnMouseEnter() override;
	void OnMouseExit() override;
	void SetOriginal_Y(float value);
private:
	EndWaveState* m_state;
	float m_originalY;
};

