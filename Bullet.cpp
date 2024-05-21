#include "Bullet.h"
#include "Game.h"
#include "Collider.h"

Bullet::Bullet(){}

void Bullet::Initialize(const char* name, TEXTURE_ID textureID, int initX, int initY, int width, int height)
{
	m_name = name;
	m_pos.x = initX;
	m_pos.y = initY;
	m_angle = 0;

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
	m_sprite->Update(m_pos.x, m_pos.y);
}

void Bullet::Render()
{
	m_sprite->Render(m_angle);
}

void Bullet::SetAngle(float angle)
{
	m_angle = angle;
}
