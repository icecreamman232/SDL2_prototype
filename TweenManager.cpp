#include "TweenManager.h"

TweenEffect* TweenManager::CreateTween(Tween::TweenEase ease, UIImage* image, float targetX, float targetY, float duration)
{
    switch (ease)
    {
        case Tween::LINEAR:
            auto newTween = new LinearTween(image, targetX, targetY, duration);
            m_tweenContainer.push_back(newTween);
            return newTween;
        break;
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
