#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(SDL_Texture* texture, int x, int y, int width, int height, int order)
{
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
	m_destRect.w = m_srcRect.w * 3;
	m_destRect.h = m_srcRect.h * 3;
}


void Sprite::Update(int x, int y)
{
	m_destRect.x = x;
	m_destRect.y = y;
	m_destRect.w = m_srcRect.w * 3;
	m_destRect.h = m_srcRect.h * 3;
}

void Sprite::Render(float angle)
{

	SDL_RenderCopyExF(Game::Renderer, m_texture, &m_srcRect, &m_destRect, angle, NULL, SDL_FLIP_NONE);
}

SDL_FRect Sprite::GetRect()
{
	return m_destRect;
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
