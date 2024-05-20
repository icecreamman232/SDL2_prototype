#include <iostream>

#include "SpaceShip.h"
#include "Game.h"
#include "Math/MathHelper.h"


SpaceShip::SpaceShip(const char* name,SDL_Texture* texturePath, int initX, int initY,int width, int height)
	:GameObject(name, texturePath,initX, initY, width, height)
{
	m_direction.x = 0;
	m_direction.y = 0;
	m_moveSpeed = 200;

	m_health.Initialize(100, 0.5);
	m_primaryWeapon = new Weapon(0.3);
	m_primaryWeapon->InitializeBullet(20,"Bullet",
		AssetManager::Instance().LoadTexture(PLAYER_NORMAL_BULLET),16, 16);
}

void SpaceShip::SetDirectionX(float value)
{
	m_direction.x = value;
}

void SpaceShip::SetDirectionY(float value)
{
	m_direction.y = value;
}

void SpaceShip::Update(float deltaTime)
{
	UpdateInput();
	UpdateMovement(deltaTime);

	GameObject::Update(deltaTime);
}

void SpaceShip::UpdateInput()
{
	if (Input::Instance().GetKeyDown(SDL_SCANCODE_A))
	{
		SetDirectionX(-1.0);
	}
	else if (Input::Instance().GetKeyDown(SDL_SCANCODE_D))
	{
		SetDirectionX(1.0);
	}
	else
	{
		SetDirectionX(0.0);
	}


	if (Input::Instance().GetKeyDown(SDL_SCANCODE_W))
	{
		SetDirectionY(-1.0);
	}
	else if (Input::Instance().GetKeyDown(SDL_SCANCODE_S))
	{
		SetDirectionY(1.0);
	}
	else
	{
		SetDirectionY(0.0);
	}

	if (Input::Instance().IsLeftMouseDown())
	{
		m_primaryWeapon->Shoot();
	}
}

void SpaceShip::UpdateMovement(float deltaTime)
{
	m_pos += m_direction * (m_moveSpeed * deltaTime);

	if (m_pos.x <= 0)
	{
		m_pos.x = 0;
	}
	else if (m_pos.x >= Game::ScreenWidth - m_destRect.w)
	{
		m_pos.x = Game::ScreenWidth - m_destRect.w;
	}

	if (m_pos.y <= 0)
	{
		m_pos.y = 0;
	}
	else if (m_pos.y >= Game::ScreenHeight - m_destRect.h)
	{
		m_pos.y = Game::ScreenHeight - m_destRect.h;
	}

	LookAt(Input::Instance().MouseX, Input::Instance().MouseY);
}


void SpaceShip::TakeDamage()
{
	m_health.TakeDamage(10);
}

float SpaceShip::GetPercentHealth()
{
	return MathHelper::Remap(m_health.GetCurrentHealth(), 0, m_health.GetMaxHealth(), 0, 1);
}


