#include "Animation.h"
#include "AssetManager.h"

Animation::Animation(TEXTURE_ID textureID, Sprite* sprite, 
	int numberFrame,float timeFrame, int widthFrame, int heightFrame)
{
	m_texture = AssetManager::Instance().LoadTexture(textureID);
	m_sprite = sprite;

	m_numFrame = numberFrame;
	m_curFrame = 0;
	m_timeFrame = timeFrame;
	m_widthFrame = widthFrame;
	m_heightFrame = heightFrame;

	m_isFinished = false;
	m_isPlaying = false;
	m_timer = 0;
	m_canLoop = false;
	m_nextAnim = nullptr;
}

void Animation::Play()
{
	if (m_isPlaying) return;

	m_isPlaying = true;
	m_timer = 0;
	m_curFrame = 0;
}

void Animation::Update(float deltaTime)
{
	if (!m_isPlaying) return;
	if (m_timer > 0)
	{
		m_timer -= deltaTime;
		return;
	}
	m_sprite->SetTexture(m_texture);
	m_sprite->SetFrame(m_curFrame);
	m_curFrame++;

	if (m_curFrame > m_numFrame)
	{
		if (m_canLoop)
		{
			m_curFrame = 0;
		}
		else 
		{
			m_isFinished = true;
			m_curFrame = m_numFrame;
			if (m_nextAnim != nullptr)
			{
				m_isPlaying = false;
				m_nextAnim->Play();
			}
		}	
	}

	m_timer = m_timeFrame;
}


