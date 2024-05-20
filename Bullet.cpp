#include "Bullet.h"
#include "Game.h"
#include "Collider.h"

Bullet::Bullet()
{

}

void Bullet::Initialize(const char* name, SDL_Texture* texture, int initX, int initY, int width, int height)
{
	m_name = name;
	m_texture = texture;
	m_pos.x = initX;
	m_pos.y = initY;
	m_angle = 0;

	m_srcRect.w = width;
	m_srcRect.h = height;
	m_srcRect.x = 0;
	m_srcRect.y = 0;

	m_destRect.x = m_pos.x;
	m_destRect.y = m_pos.y;
	m_destRect.w = m_srcRect.w * 3;
	m_destRect.h = m_srcRect.h * 3;

	m_collider = new Collider(this);

	//New game object created will be set to layer default
	SetLayer(Layer::DEFAULT);
	m_isActive = true;

	m_moveSpeed = 0;
	m_direction.x = 0;
	m_direction.y = 0;

}

void Bullet::Update(float deltaTime)
{
	m_pos += m_direction * (deltaTime * m_moveSpeed);
}

void Bullet::Render()
{
	SDL_RenderCopyExF(Game::Renderer, m_texture, &m_srcRect, &m_destRect, m_angle, NULL, SDL_FLIP_NONE);
}

void Bullet::SetAngle(float angle)
{
	m_angle = angle;
}
