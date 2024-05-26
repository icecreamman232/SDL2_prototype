#include <iostream>

#include "SpaceShip.h"
#include "Game.h"
#include "Math/MathHelper.h"


SpaceShip::SpaceShip(const char* name,TEXTURE_ID textureID, int initX, int initY,int width, int height, int order)
	:GameObject(name, textureID,initX, initY, width, height, order)
{
	m_direction.x = 0;
	m_direction.y = 0;
	m_moveSpeed = 200;

	m_health.Initialize(100, 0.5);
	m_primaryWeapon = new Weapon(0.15);
	m_primaryWeapon->InitializeBullet(20,"Bullet",
		AssetManager::Instance().LoadTexture(PLAYER_NORMAL_BULLET),16, 16);

	for (auto bullet : m_primaryWeapon->GetBulletList())
	{
		Game::m_quadTreev2->Insert(bullet);
	}

	Game::CurrentScene->Add(dynamic_cast<GameObject*>(this), RenderLayer::PLAYER);
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

	m_primaryWeapon->Update(deltaTime);

	for (auto bullet : m_primaryWeapon->GetBulletList())
	{
		Game::m_quadTreev2->Insert(bullet);
	}

	for (auto bullet : m_primaryWeapon->GetBulletList())
	{
		auto objectCollide = Game::m_quadTreev2->GetCollision(bullet, Layer::ENEMY);
		if (objectCollide != nullptr)
		{
			auto slime = static_cast<Slime*>(objectCollide);
			slime->TakeDamage(bullet->GetDamage());
			bullet->SetActive(false);
			m_primaryWeapon->DestroyBullet(bullet);
		}
	}


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
		auto shootDirection = (Vector2(Input::Instance().MouseX, Input::Instance().MouseY) - m_pos).Normalize();
		m_primaryWeapon->Shoot(m_pos, shootDirection,m_angle);
	}
}

void SpaceShip::UpdateMovement(float deltaTime)
{
	m_pos += m_direction * (m_moveSpeed * deltaTime);

	if (m_pos.x <= -m_sprite->GetRect().w)
	{
		m_pos.x = Game::ScreenWidth;
	}
	else if (m_pos.x >= Game::ScreenWidth)
	{
		m_pos.x = -m_sprite->GetRect().w;
	}

	if (m_pos.y <= -m_sprite->GetRect().h)
	{
		m_pos.y = Game::ScreenHeight;

	}
	else if (m_pos.y >= Game::ScreenHeight)
	{
		m_pos.y = -m_sprite->GetRect().h;
	}

	LookAt(Input::Instance().MouseX, Input::Instance().MouseY);
}


void SpaceShip::TakeDamage(int damage)
{
	m_health.TakeDamage(damage);
}

float SpaceShip::GetPercentHealth()
{
	return MathHelper::Remap(m_health.GetCurrentHealth(), 0, m_health.GetMaxHealth(), 0, 1);
}


