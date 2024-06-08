#pragma once
#include "Math/MathHelper.h"
#include "UIImage.h"
#include <SDL_rect.h>

class TweenEffect
{
public:
	TweenEffect(UIImage* image, float targetX, float targetY, float duration)
	{
		m_image = image;
		m_targetX = targetX;
		m_targetY = targetY;
		m_duration = duration;
		m_elapsedTime = 0;

		m_startX = m_image->GetPosX();
		m_startY = m_image->GetPosY();
	}
	virtual ~TweenEffect(){}
	virtual float TweenFormulaCalculation(float t) = 0;
	virtual void Update(float deltaTime)
	{
		if (m_elapsedTime >= m_duration)
		{
			return;
		}
		m_elapsedTime += deltaTime;
		float t = m_elapsedTime / m_duration;

		m_image->SetPosition(
			(m_startX + (m_targetX - m_startX) * TweenFormulaCalculation(t))
			, (m_startY + (m_targetY - m_startY) * TweenFormulaCalculation(t)));
	}
	virtual bool IsFinished() 
	{ 
		return m_elapsedTime >= m_duration; 
	}
	
protected:
	UIImage* m_image;
	float m_elapsedTime;
	float m_startX;
	float m_startY;
	float m_targetX;
	float m_targetY;
	float m_duration;
};


class LinearTween : public TweenEffect
{
public: 
	LinearTween(UIImage* image, float targetX, float targetY, float duration) 
		: TweenEffect(image, targetX, targetY, duration){}

	float TweenFormulaCalculation(float t) override
	{
		return t;
	}
};

class EaseInSin : public TweenEffect
{
public:
	EaseInSin(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration){}

	float TweenFormulaCalculation(float t) override
	{
		return 1 - std::cos((t * MathHelper::PI) / 2);
	}
};

class EaseOutSin : public TweenEffect
{
public:
	EaseOutSin(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration){}

	float TweenFormulaCalculation(float t)
	{
		return std::sin((t * MathHelper::PI) / 2);
	}
};

class EaseInOutSin : public TweenEffect
{
public:
	EaseInOutSin(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		return -(std::cos(MathHelper::PI * t) - 1) / 2;
	}
};

class EaseInQuad : public TweenEffect
{
public:
	EaseInQuad(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		return t*t;
	}
};

class EaseOutQuad : public TweenEffect
{
public:
	EaseOutQuad(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		return 1 - (1-t) * (1-t);
	}
};

class EaseInOutQuad : public TweenEffect
{
public:
	EaseInOutQuad(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		if (t < 0.5f)
		{
			return 2 * t * t;
		}
		else 
		{
			return 1 - std::pow(-2 * t + 2, 2) / 2;
		}
	}
};

class EaseInCubic : public TweenEffect
{
public:
	EaseInCubic(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		return t * t * t;
	}
};

class EaseOutCubic : public TweenEffect
{
public:
	EaseOutCubic(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		return 1 - std::pow(1-t,3);
	}
};

class EaseInOutCubic : public TweenEffect
{
public:
	EaseInOutCubic(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		if (t < 0.5f)
		{
			return 4 * t * t * t;
		}
		else 
		{
			return 1 - std::pow(-2 * t + 2, 3) / 2;
		}
	}
};

class EaseInQuart : public TweenEffect
{
public:
	EaseInQuart(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		return t * t * t * t;
	}
};

class EaseOutQuart : public TweenEffect
{
public:
	EaseOutQuart(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		return 1 - std::pow(1 - t, 4);
	}
};

class EaseInOutQuart : public TweenEffect
{
public:
	EaseInOutQuart(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		if (t < 0.5f)
		{
			return 8 * t * t * t * t;
		}
		else 
		{
			return 1 - std::pow(-2 * t + 2, 4);
		}
	}
};

class EaseInQuint : public TweenEffect
{
public:
	EaseInQuint(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		return t * t * t * t * t;
	}
};

class EaseOutQuint : public TweenEffect
{
public:
	EaseOutQuint(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		return 1 - std::pow( 1-t , 5);
	}
};

class EaseInOutQuint : public TweenEffect
{
public:
	EaseInOutQuint(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		if (t < 0.5f)
		{
			return 16 * t * t * t * t * t;
		}
		else 
		{
			return 1 - std::pow(-2 * t + 2, 5) / 2;
		}
	}
};

class EaseInExpo : public TweenEffect
{
public:
	EaseInExpo(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		return t == 0 ? 0 : std::pow(2, 10 * t - 10);
	}
};

class EaseOutExpo : public TweenEffect
{
public:
	EaseOutExpo(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		return t == 1 ? 1 : std::pow(2, -10 * t);
	}
};

class EaseInOutExpo : public TweenEffect
{
public:
	EaseInOutExpo(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		if (t == 0)
		{
			return 0;
		}
		else if (t == 1)
		{
			return 1;
		}
		else if(t < 0.5f)
		{
			return std::pow(2, 20 * t - 10) / 2;
		}
		else 
		{
			return (2 - std::pow(2, -20 * t + 10)) / 2;
		}
	}
};

class EaseInCirc : public TweenEffect
{
public:
	EaseInCirc(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		return 1 - std::sqrt(1 - std::pow(t, 2));
	}
};

class EaseOutCirc : public TweenEffect
{
public:
	EaseOutCirc(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		return std::sqrt(1 - std::pow(t - 1, 2));
	}
};

class EaseInOutCirc : public TweenEffect
{
public:
	EaseInOutCirc(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		return t < 0.5f
			? (1 - std::sqrt(1 - std::pow(2 * t, 2))) / 2
			: (std::sqrt(1 - std::powf(-2 * t + 2, 2)) + 1) / 2;
	}
};

class EaseInBack : public TweenEffect
{
public:
	EaseInBack(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		float c1 = 1.70158;
		float c3 = c1 + 1;
		return c3 * t * t * t - c1 * t * t;
	}
};

class EaseOutBack : public TweenEffect
{
public:
	EaseOutBack(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		float c1 = 1.70158;
		float c3 = c1 + 1;
		return 1 + c3 * std::pow(t - 1, 3) + c1 * std::pow(t - 1, 2);
	}
};

class EaseInOutBack : public TweenEffect
{
public:
	EaseInOutBack(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		float c1 = 1.70158f;
		float c2 = c1 * 1.525f;
		return t < 0.5
			? (std::pow(2 * t, 2) * ((c2 + 1) * 2 * t - c2)) / 2
			: (std::pow(2 * t - 2, 2) * ((c2 + 1) * (t * 2 - 2) + c2) + 2) / 2;

	}
};

class EaseInElastic : public TweenEffect
{
public:
	EaseInElastic(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration){}

	float TweenFormulaCalculation(float t)
	{
		auto c4 = (2 * MathHelper::PI) / 3;
		if (t == 0)
		{
			return 0;
		}
		else if (t == 1) 
		{
			return 1;
		}
		else 
		{
			return -std::pow(2, 10 * t - 10) * std::sin((t * 10 - 10.75) * c4);
		}
	}
};

class EaseOutElastic : public TweenEffect
{
public:
	EaseOutElastic(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration){}

	float TweenFormulaCalculation(float t)
	{
		auto c4 = (2 * MathHelper::PI) / 3;
		if (t == 0)
		{
			return 0;
		}
		else if (t == 1)
		{
			return 1;
		}
		else
		{
			return std::pow(2, -10 * t) * std::sin((t * 10 - 0.75) * c4) + 1;
		}
	}
};

class EaseInOutElastic : public TweenEffect
{
public:
	EaseInOutElastic(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		auto c5 = (2 * MathHelper::PI) / 4.5f;
		if (t == 0)
		{
			return 0;
		}
		else if (t == 1)
		{
			return 1;
		}
		else if(t < 0.5)
		{
			return -(std::pow(2, 20 * t - 10) * std::sin((20 * t - 11.125) * c5)) / 2;
		}
		else 
		{
			return (std::pow(2, -20 * t + 10) * std::sin((20 * t - 11.125) * c5)) / 2 + 1;

		}
	}
};

class EaseOutBounce : public TweenEffect
{
public:
	EaseOutBounce(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		float n1 = 7.5625f;
		float d1 = 2.75f;
		if (t < 1 / d1) {
			return n1 * t * t;
		}
		else if (t < 2 / d1) 
		{
			t -= 1.5 / d1;
			return n1 * t * t + 0.75;
		}
		else if (t < 2.5 / d1) 
		{
			t -= 2.25 / d1;
			return n1 * t * t + 0.9375;
		}
		else 
		{
			t -= 2.625 / d1;
			return n1 * t * t + 0.984375;
		}
	}
};

class EaseInBounce : public TweenEffect
{
public:
	EaseInBounce(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}

	float TweenFormulaCalculation(float t)
	{
		float n1 = 7.5625f;
		float d1 = 2.75f;

		if (t < 1 / d1) {
			return n1 * t * t;
		}
		else if (t < 2 / d1) {
			t -= 1.5 / d1;
			return n1 * t * t + 0.75;
		}
		else if (t < 2.5 / d1) {
			t -= 2.25 / d1;
			return n1 * t * t + 0.9375;
		}
		else {
			t -= 2.625 / d1;
			return n1 * t * t + 0.984375;
		}
	}
};

class EaseInOutBounce : public TweenEffect
{
public:
	EaseInOutBounce(UIImage* image, float targetX, float targetY, float duration)
		: TweenEffect(image, targetX, targetY, duration) {}
	float TweenFormulaCalculation(float t)
	{
		return t < 0.5
			? (1 - EaseOutBounce(1 - 2 * t)) / 2
			: (1 + EaseOutBounce(2 * t - 1)) / 2;
	}
private:
	float EaseOutBounce(float t)
	{
		float n1 = 7.5625f;
		float d1 = 2.75f;
		if (t < 1 / d1) {
			return n1 * t * t;
		}
		else if (t < 2 / d1)
		{
			t -= 1.5 / d1;
			return n1 * t * t + 0.75;
		}
		else if (t < 2.5 / d1)
		{
			t -= 2.25 / d1;
			return n1 * t * t + 0.9375;
		}
		else
		{
			t -= 2.625 / d1;
			return n1 * t * t + 0.984375;
		}
	}
};



