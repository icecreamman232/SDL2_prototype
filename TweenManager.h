#pragma once
#include "Singleton.h"
#include "TweenEffect.h"
#include "Global.h"
#include <vector>
#include "UIImage.h"

class TweenManager : public Singleton<TweenManager>
{
public:
	TweenEffect* CreateTween(Tween::TweenEase ease, UIImage* image, float targetX, float targetY, float duration);
	void Update(float deltaTime);
private:
	std::vector<TweenEffect*> m_tweenContainer;
	std::vector<int> m_toBeRemovedContainer;
};



