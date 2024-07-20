#pragma once
#include "Math/MathHelper.h"
#include "TweenFormula.h"
#include "UIImage.h"
#include <SDL_rect.h>

class TweenEffectBase
{
public:
	virtual bool IsFinished() { return true; };
	virtual void Update(float deltaTime) {};

protected:
	TweenEase m_tweenType;
	float m_duration;
	float m_elapsedTime;
};


#pragma region Tween For UI

class TweenUIPosition : public TweenEffectBase
{
public:
	TweenUIPosition(TweenEase ease, UIImage* image, float targetX, float targetY, float duration)
	{
		m_tweenType = ease;
		m_image = image;
		m_targetX = targetX;
		m_targetY = targetY;
		m_duration = duration;
		m_elapsedTime = 0;

		m_startX = m_image->GetPosX();
		m_startY = m_image->GetPosY();
	}

	void Update(float deltaTime) override
	{
		if (m_elapsedTime >= m_duration)
		{
			return;
		}
		m_elapsedTime += deltaTime;
		float t = m_elapsedTime / m_duration;

		m_image->SetPosition(
			(m_startX + (m_targetX - m_startX) * (GetTweenValue(m_tweenType, t) > 1 ? 1 : GetTweenValue(m_tweenType, t)))
			, (m_startY + (m_targetY - m_startY) * (GetTweenValue(m_tweenType, t) > 1 ? 1 : GetTweenValue(m_tweenType, t))));
	}
	bool IsFinished() override
	{ 
		return m_elapsedTime >= m_duration; 
	}
	
protected:
	
	UIImage* m_image;
	
	float m_startX;
	float m_startY;
	float m_targetX;
	float m_targetY;
};

#pragma endregion

#pragma region Tween For Values

#pragma endregion






