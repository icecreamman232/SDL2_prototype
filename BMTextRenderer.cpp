#include "BMTextRenderer.h"
#include "AssetManager.h"
#include "Game.h"

BMTextRenderer::BMTextRenderer(TEXTURE_ID textureID, std::string text,Pivot pivot, int x, int y)
{
	m_texture = AssetManager::Instance().LoadTexture(textureID);
	m_text = text;
	m_pivot = pivot;

	m_pos.x = x;
	m_pos.y = y;

	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.w = 16;
	m_srcRect.h = 16;

	m_destRect.x = x;
	m_destRect.y = y;
	m_destRect.w = 16;
	m_destRect.h = 16;

	ComputeTextSize();

	Game::CurrentScene->Add(this);
}

void BMTextRenderer::Render()
{
	int charCount = 0;
	int prevSpacing = 0;
	for (auto character : m_text)
	{
		auto ascii = static_cast<int>(character);
		auto index = ascii - m_startAsciiValue;
		auto x = index - ((index / m_maxCol) * m_maxCol);
		auto y = index / m_maxCol;
		m_srcRect.x = x * 16;
		m_srcRect.y = y * 16;

		m_destRect.x = m_pos.x + GetOffSetX() + charCount * GetSpacing(ascii) ;

		m_destRect.w = m_size;
		m_destRect.h = m_size;

		charCount++;
		SDL_RenderCopyF(Game::Renderer, m_texture, &m_srcRect, &m_destRect);
	}
}

void BMTextRenderer::ComputeTextSize()
{
	for (auto character : m_text)
	{
		auto ascii = static_cast<int>(character);
		m_textSize += ascii == 32 ? m_size : m_size / 2;
	}
}

int BMTextRenderer::GetOffSetX()
{
	switch (m_pivot)
	{
		case Pivot::LEFT:
			break;
		case Pivot::RIGHT:
			return -m_textSize;
		case Pivot::CENTER:
			return -m_textSize/2;
			break;
		case Pivot::TOP:
			break;
		case Pivot::BOTTOM:
			break;
	}
}

int BMTextRenderer::GetOffSetY()
{
	return 0;
}

