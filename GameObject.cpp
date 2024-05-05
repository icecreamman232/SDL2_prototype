#include "GameObject.h"

GameObject::GameObject(const char* texturePath, SDL_Renderer* renderer,int initX, int initY)
{
	m_renderer = renderer;
	m_texture = TextureLoader::LoadTexture(texturePath, renderer);
	m_posX = initX;
	m_posY = initY;
	m_angle = 0;

	m_srcRect.w = 18;
	m_srcRect.h = 16;
	m_srcRect.x = 0;
	m_srcRect.y = 0;

	m_destRect.x = m_posX;
	m_destRect.y = m_posY;
	m_destRect.w = m_srcRect.w * 3;
	m_destRect.h = m_srcRect.h * 3;

}

void GameObject::Update(float deltaTime)
{
	m_destRect.x = m_posX;
	m_destRect.y = m_posY;
	m_destRect.w = m_srcRect.w * 3;
	m_destRect.h = m_srcRect.h * 3;
}

void GameObject::Render()
{
	SDL_RenderCopyExF(m_renderer, m_texture, &m_srcRect, &m_destRect,m_angle,NULL,SDL_FLIP_NONE);

}

void GameObject::SetPosition(int x, int y)
{
	m_posX = x;
	m_posY = y;
}

void GameObject::SetRotation(double angle)
{
	m_angle = angle;
}

void GameObject::LookAt(int x, int y)
{
	float relativeX = x - m_posX;
	float relativeY = y - m_posY;

	m_angle = SDL_atan2(relativeY, relativeX) * (180.0 / M_PI ) + 90;
	SetRotation(m_angle);
}

