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

	m_curAlpha = 0;
	m_renderBarState = HealthBarState::HIDE;
}

void PlayerHealthBar::UpdateBar(float fillAmount)
{
	switch (m_renderBarState)
	{
		case HealthBarState::FADE_IN:
			m_timer += Game::DeltaTime;
			if (m_timer >= m_timeStep)
			{
				m_timer = 0;
				m_curAlpha += m_fadeStep;
				if (m_curAlpha >= 255)
				{
					m_curAlpha = 255;
					m_renderBarState = HealthBarState::SHOWN;
				}
			}
			break;
		case HealthBarState::FADE_OUT:
			m_timer += Game::DeltaTime;
			if (m_timer >= m_timeStep)
			{
				m_timer = 0;
				m_curAlpha-= m_fadeStep;
				if (m_curAlpha <= 0)
				{
					m_curAlpha = 0;
					m_renderBarState = HealthBarState::HIDE;
				}
			}
			
			break;
		case HealthBarState::HIDE:
			break;
		case HealthBarState::SHOWN:
			fillBarAmount = fillAmount;
			m_barRect.w = MathHelper::Remap(fillBarAmount, 0, 1, 0, m_barWidth);
			break;
	}
}

void PlayerHealthBar::Render()
{
	switch (m_renderBarState)
	{
		case HealthBarState::FADE_IN:
			SDL_SetTextureAlphaMod(m_texture, m_curAlpha);
			SDL_SetTextureColorMod(m_texture, 255, 255, 255);
			SDL_RenderCopyF(Game::Renderer, m_texture, &m_srcRect, &m_backgroundRect);
			SDL_SetTextureColorMod(m_texture, 255, 0, 0);
			SDL_RenderCopyF(Game::Renderer, m_texture, &m_srcRect, &m_barRect);
			break;
		case HealthBarState::FADE_OUT:
			break;
		case HealthBarState::SHOWN:
			Show();
			break;
		case HealthBarState::HIDE:
			break;
	}
}

void PlayerHealthBar::FadeIn(float duration)
{
	m_renderBarState = HealthBarState::FADE_IN;
	m_curAlpha = 0;
	m_fadeDuration = duration;
	m_timer = 0;
	m_timeStep = Game::DeltaTime / m_fadeDuration;
	m_fadeStep = m_timeStep * 255;

	SDL_SetTextureAlphaMod(m_texture, m_curAlpha);
	SDL_RenderCopyF(Game::Renderer, m_texture, &m_srcRect, &m_backgroundRect);
	SDL_RenderCopyF(Game::Renderer, m_texture, &m_srcRect, &m_barRect);

}

void PlayerHealthBar::FadeOut(float duration)
{
	m_renderBarState = HealthBarState::FADE_OUT;
	m_curAlpha = 1;
	m_fadeDuration = duration;
	m_timer = 0;
	m_timeStep = Game::DeltaTime / m_fadeDuration;
	m_fadeStep = m_timeStep * 255;

	SDL_SetTextureAlphaMod(m_texture, m_curAlpha);
	SDL_RenderCopyF(Game::Renderer, m_texture, &m_srcRect, &m_backgroundRect);
	SDL_RenderCopyF(Game::Renderer, m_texture, &m_srcRect, &m_barRect);

}


void PlayerHealthBar::Show()
{
	//Background
	SDL_SetTextureColorMod(m_texture, 255, 255, 255);
	SDL_RenderCopyF(Game::Renderer, m_texture, &m_srcRect, &m_backgroundRect);

	//Foreground
	SDL_SetTextureColorMod(m_texture, 255, 0, 0);
	SDL_RenderCopyF(Game::Renderer, m_texture, &m_srcRect, &m_barRect);

	UIBase::Render();
}
