#include "TweenManager.h"

TweenEffect* TweenManager::CreateTween(Tween::TweenEase ease, UIImage* image, float targetX, float targetY, float duration)
{
    switch (ease)
    {
        case Tween::LINEAR:
        {
            auto easeLinear = new LinearTween(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeLinear);
            return easeLinear;
        }
        case Tween::IN_SIN:
        {
            auto easeInSin = new EaseInSin(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeInSin);
            return easeInSin;
        }  
        case Tween::OUT_SIN:
        {
            auto easeOutSin = new EaseOutSin(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeOutSin);
            return easeOutSin;
        }

        case Tween::IN_OUT_SIN:
        {
            auto easeInOutSin = new EaseInOutSin(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeInOutSin);
            return easeInOutSin;
        }

        case Tween::IN_QUAD:
        {
            auto easeInQuad = new EaseInQuad(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeInQuad);
            return easeInQuad;
        }

        case Tween::OUT_QUAD:
        {
            auto easeOutQuad = new EaseOutQuad(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeOutQuad);
            return easeOutQuad;
        }

        case Tween::IN_OUT_QUAD:
        {
            auto easeInOutQuad = new EaseInOutQuad(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeInOutQuad);
            return easeInOutQuad;
        }

        case Tween::IN_CUBIC:
        {
            auto easeInCubic = new EaseInCubic(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeInCubic);
            return easeInCubic;
        }

        case Tween::OUT_CUBIC:
        {
            auto easeOutCubic = new EaseOutCubic(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeOutCubic);
            return easeOutCubic;
        }

        case Tween::IN_OUT_CUBIC:
        {
            auto easeInOutCubic = new EaseInOutCubic(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeInOutCubic);
            return easeInOutCubic;
        }

        case Tween::IN_QUART:
        {
            auto easeInQuart = new EaseInQuart(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeInQuart);
            return easeInQuart;
        }

        case Tween::OUT_QUART:
        {
            auto easeOutQuart = new EaseOutQuart(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeOutQuart);
            return easeOutQuart;
        }

        case Tween::IN_OUT_QUART:
        {
            auto easeInOutQuart = new EaseInOutQuart(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeInOutQuart);
            return easeInOutQuart;
        }

        case Tween::IN_QUINT:
        {
            auto easeInQuint = new EaseInQuint(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeInQuint);
            return easeInQuint;
        }

        case Tween::OUT_QUINT:
        {
            auto easeOutQuint = new EaseOutQuint(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeOutQuint);
            return easeOutQuint;
        }

        case Tween::IN_OUT_QUINT:
        {
            auto easeInOutQuint = new EaseInOutQuint(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeInOutQuint);
            return easeInOutQuint;
        }

        case Tween::IN_EXPO:
        {
            auto easeInExpo = new EaseInExpo(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeInExpo);
            return easeInExpo;
        }

        case Tween::OUT_EXPO:
        {
            auto easeOutExpo = new EaseOutExpo(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeOutExpo);
            return easeOutExpo;
        }

        case Tween::IN_OUT_EXPO:
        {
            auto easeInOutExpo = new EaseInOutExpo(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeInOutExpo);
            return easeInOutExpo;
        }

        case Tween::IN_CIRC:
        {
            auto easeInCirc = new EaseInCirc(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeInCirc);
            return easeInCirc;
        }

        case Tween::OUT_CIRC:
        {
            auto easeOutCirc = new EaseOutCirc(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeOutCirc);
            return easeOutCirc;
        }

        case Tween::IN_OUT_CIRC:
        {
            auto easeInOutCirc = new EaseInOutCirc(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeInOutCirc);
            return easeInOutCirc;
        }

        case Tween::IN_BACK:
        {
            auto easeInBack = new EaseInBack(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeInBack);
            return easeInBack;
        }

        case Tween::OUT_BACK:
        {
            auto easeOutBack = new EaseOutBack(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeOutBack);
            return easeOutBack;
        }

        case Tween::IN_OUT_BACK:
        {
            auto easeInOutBack = new EaseInOutBack(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeInOutBack);
            return easeInOutBack;
        }

        case Tween::IN_ELASTIC:
        {
            auto easeInElastic = new EaseInElastic(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeInElastic);
            return easeInElastic;
        }
        case Tween::OUT_ELASTIC:
        {
            auto easeOutElastic = new EaseOutElastic(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeOutElastic);
            return easeOutElastic;
        }
        case Tween::IN_OUT_ELASTIC:
        {
            auto easeInOutElastic = new EaseInOutElastic(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeInOutElastic);
            return easeInOutElastic;
        }

        case Tween::IN_BOUNCE:
        {
            auto easeInBounce = new EaseInBounce(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeInBounce);
            return easeInBounce;
        }
        case Tween::OUT_BOUNCE:
        {
            auto easeOutBounce = new EaseOutBounce(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeOutBounce);
            return easeOutBounce;
        }
        case Tween::IN_OUT_BOUNCE:
        {
            auto easeInOutBounce = new EaseInOutBounce(image, targetX, targetY, duration);
            m_tweenContainer.push_back(easeInOutBounce);
            return easeInOutBounce;
        }
    }
}

void TweenManager::Update(float deltaTime)
{
    for (size_t i = 0; i< m_tweenContainer.size();i++)
    {
        if (m_tweenContainer[i]->IsFinished())
        {
            m_toBeRemovedContainer.push_back(m_tweenContainer[i]);
        }
        else 
        {
            m_tweenContainer[i]->Update(deltaTime);
        }
    }

    if (!m_toBeRemovedContainer.empty())
    {
        for (size_t i = 0; i < m_toBeRemovedContainer.size(); i++)
        {
            m_tweenContainer.erase(m_tweenContainer.begin() + i);
            delete m_toBeRemovedContainer[i];
        }
        m_toBeRemovedContainer.clear();
    }
}
