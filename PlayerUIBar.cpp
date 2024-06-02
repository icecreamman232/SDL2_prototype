#include "Game.h"
#include "PlayerUIBar.h"
#include "Math/MathHelper.h"

PlayerUIBar::PlayerUIBar(float x, float y, float width, float height)
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

	m_barColor = { 255,255,255 };
	m_backgroundColor = { 255,255,255 };

	m_curAlpha = 0;
	m_renderBarState = BarState::HIDE;
}

void PlayerUIBar::SetBarFillInstant(float fillAmount)
{
	fillBarAmount = fillAmount;
	m_barRect.w = MathHelper::Remap(fillBarAmount, 0, 1, 0, m_barWidth);
}

void PlayerUIBar::SetBarColor(SDL_Color color)
{
	m_barColor = color;
}

void PlayerUIBar::SetBackgroundColor(SDL_Color color)
{
	m_backgroundColor = color;
}

void PlayerUIBar::UpdateBar(float fillAmount)
{
	switch (m_renderBarState)
	{
		case BarState::FADE_IN:
			m_timer += Game::DeltaTime;
			if (m_timer >= m_timeStep)
			{
				m_timer = 0;
				m_curAlpha += m_fadeStep;
				if (m_curAlpha >= 255)
				{
					m_curAlpha = 255;
					m_renderBarState = BarState::SHOWN;
				}
			}
			break;
		case BarState::FADE_OUT:
			m_timer += Game::DeltaTime;
			if (m_timer >= m_timeStep)
			{
				m_timer = 0;
				m_curAlpha-= m_fadeStep;
				if (m_curAlpha <= 0)
				{
					m_curAlpha = 0;
					m_renderBarState = BarState::HIDE;
				}
			}
			
			break;
		case BarState::HIDE:
			break;
		case BarState::SHOWN:
			fillBarAmount = fillAmount > 1 ? 1 : fillAmount;
			m_barRect.w = MathHelper::Remap(fillBarAmount, 0, 1, 0, m_barWidth);
			break;
	}
}

void PlayerUIBar::Render()
{
	switch (m_renderBarState)
	{
		case BarState::FADE_IN:
			SDL_SetTextureAlphaMod(m_texture, m_curAlpha);
			SDL_SetTextureColorMod(m_texture, m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b);
			SDL_RenderCopyF(Game::Renderer, m_texture, &m_srcRect, &m_backgroundRect);
			SDL_SetTextureColorMod(m_texture, m_barColor.r, m_barColor.g, m_barColor.b);
			SDL_RenderCopyF(Game::Renderer, m_texture, &m_srcRect, &m_barRect);
			break;
		case BarState::FADE_OUT:
			break;
		case BarState::SHOWN:
			Show();
			break;
		case BarState::HIDE:
			break;
	}
}

void PlayerUIBar::FadeIn(float duration)
{
	m_renderBarState = BarState::FADE_IN;
	m_curAlpha = 0;
	m_fadeDuration = duration;
	m_timer = 0;
	m_timeStep = Game::DeltaTime / m_fadeDuration;
	m_fadeStep = m_timeStep * 255;

	SDL_SetTextureAlphaMod(m_texture, m_curAlpha);
	SDL_RenderCopyF(Game::Renderer, m_texture, &m_srcRect, &m_backgroundRect);
	SDL_RenderCopyF(Game::Renderer, m_texture, &m_srcRect, &m_barRect);

}

void PlayerUIBar::FadeOut(float duration)
{
	m_renderBarState = BarState::FADE_OUT;
	m_curAlpha = 1;
	m_fadeDuration = duration;
	m_timer = 0;
	m_timeStep = Game::DeltaTime / m_fadeDuration;
	m_fadeStep = m_timeStep * 255;

	SDL_SetTextureAlphaMod(m_texture, m_curAlpha);
	SDL_RenderCopyF(Game::Renderer, m_texture, &m_srcRect, &m_backgroundRect);
	SDL_RenderCopyF(Game::Renderer, m_texture, &m_srcRect, &m_barRect);

}


void PlayerUIBar::Show()
{
	//Background
	SDL_SetTextureColorMod(m_texture, m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b);
	SDL_RenderCopyF(Game::Renderer, m_texture, &m_srcRect, &m_backgroundRect);

	//Foreground
	SDL_SetTextureColorMod(m_texture, m_barColor.r, m_barColor.g, m_barColor.b);
	SDL_RenderCopyF(Game::Renderer, m_texture, &m_srcRect, &m_barRect);

	UIBase::Render();
}
