#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(SDL_Texture* texture, float x, float y, int width, int height, int order, bool isUI)
{
	m_isUI = isUI;
	m_order = 0;
	m_texture = texture;
	m_width = width;
	m_height = height;

	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.w = width;
	m_srcRect.h = height;
	
	m_destRect.x = x;
	m_destRect.y = y;
	m_destRect.w = m_srcRect.w * (m_isUI ? 1.0f : 3.0f);
	m_destRect.h = m_srcRect.h * (m_isUI ? 1.0f : 3.0f);

	SDL_GetTextureColorMod(m_texture, &m_originalColor.r, &m_originalColor.g, &m_originalColor.b);
	SDL_GetTextureAlphaMod(m_texture, &m_originalAlpha);

	m_tintColor = m_originalColor;
	//If texture hasnt been color modified, the alpha will be 0, 
	// so here we force it to be 255(1) for later usage
	m_originalAlpha = 255; 
	m_tintColor.a = m_originalAlpha;
	m_originalColor.a = m_originalAlpha;
	SDL_SetTextureColorMod(m_texture, m_originalColor.r, m_originalColor.g, m_originalColor.b);

	m_curAlpha = m_originalAlpha;
}


void Sprite::Update(float x, float y)
{
	m_destRect.x = x;
	m_destRect.y = y;
	m_destRect.w = m_srcRect.w * (m_isUI ? 1.0f : 3.0f);
	m_destRect.h = m_srcRect.h * (m_isUI ? 1.0f : 3.0f);
}

void Sprite::Render(float angle)
{
	if (m_tintColor.r != m_originalColor.r 
		|| m_tintColor.g != m_originalColor.g
		|| m_tintColor.b != m_originalColor.b)
	{
		SDL_SetTextureColorMod(m_texture, m_tintColor.r, m_tintColor.g, m_tintColor.b);
	}
	else 
	{
		SDL_SetTextureColorMod(m_texture, m_originalColor.r, m_originalColor.g, m_originalColor.b);
	}
	
	SDL_SetTextureAlphaMod(m_texture, m_curAlpha);

	SDL_RenderCopyExF(Game::Renderer, m_texture, &m_srcRect, &m_destRect, angle, NULL, SDL_FLIP_NONE);
}

SDL_FRect Sprite::GetRect()
{
	return m_destRect;
}

SDL_FRect* Sprite::GetRectPointer()
{
	return &m_destRect;
}

void Sprite::SetFrame(int index)
{
	m_srcRect.x += index * m_srcRect.w;
	//m_srcRect.y += index * m_srcRect.h;
}

void Sprite::SetTexture(SDL_Texture* newTexture)
{
	m_texture = newTexture;
}

void Sprite::TintColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	m_tintColor = { r,g,b };
	m_curAlpha = a;
}

void Sprite::ResetColor()
{
	m_tintColor = m_originalColor;
	m_curAlpha = m_originalAlpha;
}
