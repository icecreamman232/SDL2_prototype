#include "Game.h"
#include "PlayerHealthBar.h"
#include "Math/MathHelper.h"

PlayerHealthBar::PlayerHealthBar(int x, int y, int width, int height)
{
	fillBarAmount = 1;
	m_barWidth = width;

	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.w = width;
	m_srcRect.h = height;

	m_barRect.x = x;
	m_barRect.y = y;
	m_barRect.w = width;
	m_barRect.h = height;

	m_backgroundRect.x = x;
	m_backgroundRect.y = y;
	m_backgroundRect.w = width;
	m_backgroundRect.h = height;

	m_texture = AssetManager::Instance().LoadTexture(WHITE_BAR_UI);
}

void PlayerHealthBar::UpdateBar()
{
	//fillBarAmount = fillAmount;
	m_barRect.w = MathHelper::Remap(fillBarAmount, 0, 1, 0, m_barWidth);
}

void PlayerHealthBar::Render()
{
	SDL_SetTextureColorMod(m_texture, 255, 255, 255);
	SDL_RenderCopyF(Game::Renderer, m_texture, &m_srcRect, &m_backgroundRect);


	SDL_SetTextureColorMod(m_texture, 255, 0, 0);
	SDL_RenderCopyF(Game::Renderer, m_texture, &m_srcRect, &m_barRect);
}
