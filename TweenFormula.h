#pragma once

#include "Global.h"
using namespace Tween;


static float LinearTweenGetValue(float t)
{
	return t;
}

static float EaseInSinGetValue(float t)
{
	return 1 - std::cos((t * MathHelper::PI) / 2);
}

static float EaseOutSinGetValue(float t)
{
	return std::sin((t * MathHelper::PI) / 2);
}

static float EaseInOutSinGetValue(float t)
{
	return -(std::cos(MathHelper::PI * t) - 1) / 2;
}

static float EaseInQuadGetValue(float t)
{
	return t * t;
}

static float EaseOutQuadGetValue(float t)
{
	return 1 - (1 - t) * (1 - t);
}

static float EaseInOutQuadGetValue(float t)
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

static float EaseInCubicGetValue(float t)
{
	return t * t * t;
}

static float EaseOutCubicGetValue(float t)
{
	return 1 - std::pow(1 - t, 3);
}

static float EaseInOutCubicGetValue(float t)
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

static float EaseInQuartGetValue(float t)
{
	return t * t * t * t;
}

static float EaseOutQuartGetValue(float t)
{
	return 1 - std::pow(1 - t, 4);
}

static float EaseInOutQuartGetValue(float t)
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

static float EaseInQuintGetValue(float t)
{
	return t * t * t * t;
}

static float EaseOutQuintGetValue(float t)
{
	return 1 - std::pow(1 - t, 5);
}

static float EaseInOutQuintGetValue(float t)
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

static float EaseInExpoGetValue(float t)
{
	return t == 0 ? 0 : std::pow(2, 10 * t - 10);
}

static float EaseOutExpoGetValue(float t)
{
	return t == 1 ? 1 : std::pow(2, -10 * t);
}

static float EaseInOutExpoGetValue(float t)
{
	if (t == 0)
	{
		return 0;
	}
	else if (t == 1)
	{
		return 1;
	}
	else if (t < 0.5f)
	{
		return std::pow(2, 20 * t - 10) / 2;
	}
	else
	{
		return (2 - std::pow(2, -20 * t + 10)) / 2;
	}
}

static float EaseInCircGetValue(float t)
{
	return 1 - std::sqrt(1 - std::pow(t, 2));
}

static float EaseOutCircGetValue(float t)
{
	return std::sqrt(1 - std::pow(t - 1, 2));
}

static float EaseInOutCircGetValue(float t)
{
	return t < 0.5f
		? (1 - std::sqrt(1 - std::pow(2 * t, 2))) / 2
		: (std::sqrt(1 - std::powf(-2 * t + 2, 2)) + 1) / 2;
}

static float EaseInBackGetValue(float t)
{
	float c1 = 1.70158;
	float c3 = c1 + 1;
	return c3 * t * t * t - c1 * t * t;
}

static float EaseOutBackGetValue(float t)
{
	float c1 = 1.70158;
	float c3 = c1 + 1;
	return 1 + c3 * std::pow(t - 1, 3) + c1 * std::pow(t - 1, 2);
}

static float EaseInOutBackGetValue(float t)
{
	float c1 = 1.70158f;
	float c2 = c1 * 1.525f;
	return t < 0.5
		? (std::pow(2 * t, 2) * ((c2 + 1) * 2 * t - c2)) / 2
		: (std::pow(2 * t - 2, 2) * ((c2 + 1) * (t * 2 - 2) + c2) + 2) / 2;
}

static float EaseInElasticGetValue(float t)
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

static float EaseOutElasticGetValue(float t)
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

static float EaseInOutElasticGetValue(float t)
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
	else if (t < 0.5)
	{
		return -(std::pow(2, 20 * t - 10) * std::sin((20 * t - 11.125) * c5)) / 2;
	}
	else
	{
		return (std::pow(2, -20 * t + 10) * std::sin((20 * t - 11.125) * c5)) / 2 + 1;
	}
}


static float EaseOutBounceGetValue(float t)
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

static float EaseInBounceGetValue(float t)
{
	return 1 - EaseOutBounceGetValue(1 - t);
}

static float EaseInOutBounceGetValue(float t)
{
	return t < 0.5
		? (1 - EaseOutBounceGetValue(1 - 2 * t)) / 2
		: (1 + EaseOutBounceGetValue(2 * t - 1)) / 2;
}

static float GetTweenValue(TweenEase m_tweenType, float t)
{
	switch (m_tweenType)
	{
	case Tween::LINEAR:
		return LinearTweenGetValue(t);
	case Tween::IN_SIN:
		return EaseInSinGetValue(t);
	case Tween::OUT_SIN:
		return EaseOutSinGetValue(t);
	case Tween::IN_OUT_SIN:
		return EaseInOutSinGetValue(t);
	case Tween::IN_QUAD:
		return EaseInQuadGetValue(t);
	case Tween::OUT_QUAD:
		return EaseOutQuadGetValue(t);
	case Tween::IN_OUT_QUAD:
		return EaseInOutQuadGetValue(t);
	case Tween::IN_CUBIC:
		return EaseInCubicGetValue(t);
	case Tween::OUT_CUBIC:
		return EaseOutCubicGetValue(t);
	case Tween::IN_OUT_CUBIC:
		return EaseInOutCubicGetValue(t);
	case Tween::IN_QUART:
		return EaseInQuartGetValue(t);
	case Tween::OUT_QUART:
		return EaseOutQuartGetValue(t);
	case Tween::IN_OUT_QUART:
		return EaseInOutQuartGetValue(t);
	case Tween::IN_QUINT:
		return EaseInQuintGetValue(t);
	case Tween::OUT_QUINT:
		return EaseOutQuintGetValue(t);
	case Tween::IN_OUT_QUINT:
		return EaseInOutQuintGetValue(t);
	case Tween::IN_EXPO:
		return EaseInExpoGetValue(t);
	case Tween::OUT_EXPO:
		return EaseOutExpoGetValue(t);
	case Tween::IN_OUT_EXPO:
		return EaseInOutExpoGetValue(t);
	case Tween::IN_CIRC:
		return EaseInCircGetValue(t);
	case Tween::OUT_CIRC:
		return EaseOutCircGetValue(t);
	case Tween::IN_OUT_CIRC:
		return EaseInOutCircGetValue(t);
	case Tween::IN_BACK:
		return EaseInBackGetValue(t);
	case Tween::OUT_BACK:
		return EaseOutBackGetValue(t);
	case Tween::IN_OUT_BACK:
		return EaseInOutBackGetValue(t);
	case Tween::IN_ELASTIC:
		return EaseInElasticGetValue(t);
	case Tween::OUT_ELASTIC:
		return EaseOutElasticGetValue(t);
	case Tween::IN_OUT_ELASTIC:
		return EaseInOutElasticGetValue(t);
	case Tween::IN_BOUNCE:
		return EaseInBounceGetValue(t);
	case Tween::OUT_BOUNCE:
		return EaseOutBounceGetValue(t);
	case Tween::IN_OUT_BOUNCE:
		return EaseInOutBounceGetValue(t);
	}
}


