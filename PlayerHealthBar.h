#pragma once
#include "UIBase.h"

class PlayerHealthBar : public UIBase
{
public:
	float fillBarAmount;
	PlayerHealthBar(int x,int y,int width, int height);
	void UpdateBar(float fillAmount);
	void Render() override;
private:
	float m_barWidth;

	SDL_Rect m_srcRect;
	SDL_FRect m_backgroundRect;
	SDL_FRect m_barRect;
	SDL_Texture* m_texture;
};

