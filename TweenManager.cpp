#include "TweenManager.h"
#include "TweenFormula.h"

TweenUIPosition* TweenManager::CreateTween(Tween::TweenEase ease, UIImage* image, float targetX, float targetY, float duration)
{
    auto tweenUIPos = new TweenUIPosition(ease, image, targetX, targetY, duration);
    m_tweenContainer.push_back(tweenUIPos);
    return tweenUIPos;
}

TweenUIAlpha* TweenManager::CreateTween(Tween::TweenEase ease, UIImage* image, float targetAlpha, float duration)
{
    auto tweenUIAlpha = new TweenUIAlpha(ease, image, targetAlpha, duration);
    m_tweenContainer.push_back(tweenUIAlpha);
    return tweenUIAlpha;
}

void TweenManager::Update(float deltaTime)
{
    for (size_t i = 0; i< m_tweenContainer.size();i++)
    {
        if (m_tweenContainer[i]->IsFinished())
        {
            m_toBeRemovedContainer.push_back(i);
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
            size_t indexToRemove = m_toBeRemovedContainer[i];
            if (indexToRemove < m_tweenContainer.size())
            {
                delete m_tweenContainer[indexToRemove];
                m_tweenContainer.erase(m_tweenContainer.begin() + indexToRemove);
            }
        }
        m_toBeRemovedContainer.clear();
    }
}
