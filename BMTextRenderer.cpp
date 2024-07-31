#include "BMTextRenderer.h"
#include "AssetManager.h"
#include "Game.h"

void BMTextRenderer::Initialize(TEXTURE_ID textureID, std::string text, Pivot pivot, float x, float y)
{
	m_texture = AssetManager::Instance().GetTexture(textureID, false);
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

	m_id = s_next_UIID;
	s_next_UIID++;
}

void BMTextRenderer::Render()
{
	if (!m_isActive) return;

	int charCount = 0;
	int prevSpacing = 0;
	float prevW = 0;

	for (auto character : m_text)
	{
		auto ascii = static_cast<int>(character);
		auto index = ascii - m_startAsciiValue;
		auto x = index - ((index / m_maxCol) * m_maxCol);
		auto y = index / m_maxCol;

		auto charInfo = AssetManager::Instance().GetCharacterInfo(ascii);

		m_srcRect.x = charInfo.XCoord;
		m_srcRect.y = charInfo.YCoord;
		m_srcRect.w = charInfo.Width;
		m_srcRect.h = charInfo.Height;

		m_destRect.w = m_srcRect.w * (m_size / 16.0f);
		m_destRect.h = m_srcRect.h * (m_size / 16.0f);
		

		m_destRect.x = m_pos.x + GetOffSetX() + charCount * m_spacing + prevW;
		//std::cout << "X " << m_destRect.x << std::endl;

		m_destRect.y = m_pos.y - m_destRect.h;

		prevW += m_destRect.w;

		charCount++;
		
		//SDL_SetRenderDrawColor(Game::Renderer, 255, 0, 0, 255);
		//SDL_RenderDrawRectF(Game::Renderer, &m_destRect);
		SDL_RenderCopyF(Game::Renderer, m_texture, &m_srcRect, &m_destRect);
	}
}

void BMTextRenderer::SetSpacing(float spacing)
{
	m_spacing = spacing;
	ComputeTextSize();
}

void BMTextRenderer::SetSize(float size)
{
	m_size = size;
	ComputeTextSize();
}

/// <summary>
/// Get size of character
/// </summary>
/// <returns></returns>
float BMTextRenderer::GetSize()
{
	return m_size;
}

/// <summary>
/// Get size of whole text
/// </summary>
/// <returns></returns>
float BMTextRenderer::GetTextSize()
{
	return m_textSize;
}

void BMTextRenderer::SetPosition(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
}

void BMTextRenderer::ComputeTextSize()
{
	m_textSize = 0;
	for (auto character : m_text)
	{
		auto ascii = static_cast<int>(character);
		auto charInfo = AssetManager::Instance().GetCharacterInfo(ascii);

		m_textSize += charInfo.Width * (m_size / 16.0f); + m_spacing;
	}
}

/// <summary>
/// Depends on pivot for the text, the offset will be calculated here
/// </summary>
/// <returns></returns>
float BMTextRenderer::GetOffSetX()
{
	switch (m_pivot)
	{
		case Pivot::LEFT:
			return 0.0f;
		case Pivot::RIGHT:
			return -m_textSize;
		case Pivot::CENTER:
			return -m_textSize/2;
		case Pivot::TOP:
			return 0.0f;
		case Pivot::BOTTOM:
			return 0.0f;
		default:
			return 0.0f;
	}
}

float BMTextRenderer::GetOffSetY()
{
	return 0;
}


