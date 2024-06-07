#pragma once
#include "UIImage.h"
#include <SDL_rect.h>

class TweenEffect
{
public:
	virtual ~TweenEffect(){}
	virtual void Update(float deltaTime) = 0;
	virtual bool IsFinished() = 0;
};


class LinearTween : public TweenEffect
{
public: 
	LinearTween(UIImage* image, float targetX, float targetY, float duration)
	{
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
			(m_startX + (m_targetX - m_startX) * t)
			, (m_startY + (m_targetY - m_startY) * t));
	}

	bool IsFinished() override { return m_elapsedTime >= m_duration; };

private:
	UIImage* m_image;
	float m_elapsedTime;
	float m_startX;
	float m_startY;
	float m_targetX;
	float m_targetY;
	float m_duration;
};

