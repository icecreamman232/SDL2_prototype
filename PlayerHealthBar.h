#pragma once
#include "UIBase.h"

class PlayerHealthBar : public UIBase
{
public:
	float fillBarAmount;
	PlayerHealthBar(int x,int y,int width, int height);
	void FadeIn(float duration = 0.5f);
	void FadeOut(float duration = 0.5f);
	void UpdateBar(float fillAmount);
	void Render() override;

private:
	enum HealthBarState
	{
		FADE_IN,
		FADE_OUT,
		SHOWN,
		HIDE,
	};

	void Show();

	
	float m_fadeDuration;
	float m_timeStep;
	float m_timer;

	int m_fadeStep;
	int m_curAlpha;

	float m_barWidth;
	HealthBarState m_renderBarState;
	SDL_Rect m_srcRect;
	SDL_FRect m_backgroundRect;
	SDL_FRect m_barRect;
	SDL_Texture* m_texture;
};

