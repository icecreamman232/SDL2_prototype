#include <iostream>

#include "Slime.h"
#include "SpaceShip.h"
#include "Game.h"
#include "Math/MathHelper.h"
#include "XPEventDispatcher.h"
#include "PlayerLevelUpEventDispatcher.h"


SpaceShip::SpaceShip(const char* name,TEXTURE_ID textureID, int initX, int initY,int width, int height, int order)
	:GameObject(name, textureID,initX, initY, width, height, order)
{
	m_direction.x = 0;
	m_direction.y = 0;
	m_moveSpeed = 200;
	m_invulnerableDuration = 0.5f;
	m_flickerInterval = 0.1f;
	m_flickerTimer = 0.0;



	m_health.Initialize(100, m_invulnerableDuration);
	m_primaryWeapon = new Weapon(0.15);
	m_primaryWeapon->InitializeBullet(20,"Bullet",
		AssetManager::Instance().LoadTexture(PLAYER_NORMAL_BULLET),16, 16);

	for (auto bullet : m_primaryWeapon->GetBulletList())
	{
		Game::m_quadTreev2->Insert(bullet);
	}

	//Listen to death event of enemy
	XPEventDispatcher::Attach(this);

	//TODO:Load xp from savefile. For now it's always zero when player enter gameplay
	m_xpController.Initialize(10);

	m_levelUpSFX = Mix_LoadWAV("Asset/Sound/level-up.wav");
	Mix_VolumeChunk(m_levelUpSFX, MIX_MAX_VOLUME / 3);

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
			//std::cout << "BULLET HIT " << slime->GetID() << "\n";
		}
	}

	if (m_health.IsInvulernable())
	{
		m_flickerTimer += deltaTime;
		if (m_flickerTimer >= m_flickerInterval)
		{
			auto curColor = m_sprite->GetColor();
			if (curColor.r == 255
				&& curColor.g == 255
				&& curColor.b == 255)
			{
				m_sprite->TintColor(255, 0, 0, 255);
			}
			else 
			{
				m_sprite->TintColor(255, 255, 255, 255);
			}
			m_flickerTimer = 0;
		}
	}
	else 
	{
		//Reset tint color to white
		auto curColor = m_sprite->GetColor();
		if (curColor.r != 255
			|| curColor.g != 255
			|| curColor.b != 255)
		{
			m_sprite->TintColor(255, 255, 255, 255);
		}
	}


	GameObject::Update(deltaTime);
}


void SpaceShip::OnTriggerEvent(const XPEvent& eventType)
{
	//std::cout << "XP Gain: "<< eventType.XPGain << "\n";
	m_xpController.AddXP(eventType.XPGain);

	//Just level up
	if (m_xpController.GetCurrentXP() == 0)
	{
		Mix_PlayChannel(-1, m_levelUpSFX, 0);
		PlayerLevelUpEventDispatcher::Trigger(
			LevelUpEvent{
				m_xpController.GetCurrentLv(),
				m_xpController.GetCurrentLv() - 1 });
	}
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


