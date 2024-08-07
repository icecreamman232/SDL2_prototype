#pragma once
#include "UIBase.h"

class PlayerUIBar : public UIBase
{
public:
	float fillBarAmount;
	PlayerUIBar(float x, float y, float width, float height);
	void SetBarFillInstant(float fillAmount);
	void SetBarColor(SDL_Color color);
	void SetBackgroundColor(SDL_Color color);
	void FadeIn(float duration = 0.5f);
	void FadeOut(float duration = 0.5f);
	void UpdateBar(float fillAmount);
	void Render() override;

private:
	enum BarState
	{
		FADE_IN,
		FADE_OUT,
		SHOWN,
		HIDE,
	};

	void Show();

	SDL_Color m_barColor;
	SDL_Color m_backgroundColor;

	float m_fadeDuration;
	float m_timeStep;
	float m_timer;

	float m_fadeStep;
	int m_curAlpha;

	float m_barWidth;
	BarState m_renderBarState;
	SDL_Rect m_srcRect;
	SDL_FRect m_backgroundRect;
	SDL_FRect m_barRect;
	SDL_Texture* m_texture;
};

