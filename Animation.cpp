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
}

void Animation::Play()
{
	if (m_isPlaying) return;
	m_isPlaying = true;
	m_timer = 0;
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
	m_timer = m_timeFrame;
}


