#include "GameObject.h"
#include "Collider.h"

GameObject::GameObject(const char* texturePath, SDL_Renderer* renderer,int initX, int initY)
{
	m_renderer = renderer;
	m_texture = TextureLoader::LoadTexture(texturePath, renderer);
	m_pos.x = initX;
	m_pos.y = initY;
	m_angle = 0;

	m_srcRect.w = 18;
	m_srcRect.h = 16;
	m_srcRect.x = 0;
	m_srcRect.y = 0;

	m_destRect.x = m_pos.x;
	m_destRect.y = m_pos.y;
	m_destRect.w = m_srcRect.w * 3;
	m_destRect.h = m_srcRect.h * 3;

	m_collider = new Collider(this);
}

void GameObject::Update(float deltaTime)
{
	m_destRect.x = m_pos.x;
	m_destRect.y = m_pos.y;
	m_destRect.w = m_srcRect.w * 3;
	m_destRect.h = m_srcRect.h * 3;
}

void GameObject::Render()
{
	SDL_RenderCopyExF(m_renderer, m_texture, &m_srcRect, &m_destRect,m_angle,NULL,SDL_FLIP_NONE);

}

void GameObject::SetPosition(int x, int y)
{
	m_pos.x = x;
	m_pos.y = y;
}

void GameObject::SetRotation(double angle)
{
	m_angle = angle;
}

void GameObject::LookAt(int x, int y)
{
	float relativeX = x - m_pos.x;
	float relativeY = y - m_pos.y;

	m_angle = SDL_atan2(relativeY, relativeX) * (180.0 / M_PI ) + 90;
	SetRotation(m_angle);
}

bool GameObject::IsCollideWith(GameObject* other)
{
	return m_collider->IsCollideWith(other);
}

const SDL_FRect GameObject::Rect()
{
	return m_destRect;
}

