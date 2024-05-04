#include "GameObject.h"

GameObject::GameObject(const char* texturePath, SDL_Renderer* renderer,int initX, int initY)
{
	m_renderer = renderer;
	m_texture = TextureLoader::LoadTexture(texturePath, renderer);
	m_posX = initX;
	m_posY = initY;
}

void GameObject::Update()
{
	m_srcRect.w = 18;
	m_srcRect.h = 16;
	m_srcRect.x = 0;
	m_srcRect.y = 0;

	m_destRect.x = m_posX;
	m_destRect.y = m_posY;
	m_destRect.w = m_srcRect.w * 3;
	m_destRect.h = m_srcRect.h * 3;
}

void GameObject::Render()
{
	SDL_RenderCopy(m_renderer, m_texture, &m_srcRect, &m_destRect);
}
