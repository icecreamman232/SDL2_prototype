#include "Bullet.h"
#include "Game.h"


Bullet::Bullet(int id, const char* name, SDL_Texture* texture, int initX, int initY, int width, int height)
	: GameObject(name, texture, initX, initY, width, height)
{
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
