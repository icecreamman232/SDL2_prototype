#include "Global.h"
#include "Bullet.h"
#include "Game.h"
#include "Collider.h"
#include "Weapon.h"

Bullet::Bullet()
{
}

void Bullet::Initialize(Weapon* weaponOwner, const char* name, TEXTURE_ID textureID, float initX, float initY, int width, int height)
{
	m_isActive = true;

	m_weapon = weaponOwner;

	m_pos.x = initX;
	m_pos.y = initY;
	m_angle = 0;

	//New game object created will be set to layer default
	SetLayer(Layer::DEFAULT);
	
	m_moveSpeed = 800;
	m_direction.x = 0;
	m_direction.y = 0;

	//Prevent duplicate init not neccessary infos
	if (!m_isInitialized)
	{
		m_name = name;
		m_sprite = new Sprite(AssetManager::Instance().LoadTexture(textureID), initX, initY, width, height, 5);
		Game::CurrentScene->Add(this, RenderLayer::WEAPON);
		m_collider = new Collider(this);
		m_minDamage = 10;
		m_maxDamage = 15;

		m_id = s_nextID;
		s_nextID++;
		m_isInitialized = true;
	}
}

void Bullet::Update(float deltaTime)
{
	if (!m_isActive) return;
	m_pos += m_direction * (deltaTime * m_moveSpeed);
	m_sprite->Update(m_pos.x, m_pos.y);

	if (m_pos.x <= 0)
	{
		Remove();
	}
	else if (m_pos.x >= g_WindowSettings.Width - m_sprite->GetRect().w)
	{
		Remove();
	}

	if (m_pos.y <= 0)
	{
		Remove();
	}
	else if (m_pos.y >= g_WindowSettings.Height - m_sprite->GetRect().h)
	{
		Remove();
	}

}

void Bullet::Render()
{
	if (!m_isActive) return;
	m_sprite->Render(m_angle);
}

void Bullet::SetAngle(float angle)
{
	m_angle = angle;
}

void Bullet::SetDirection(Vector2 direction)
{
	m_direction = direction;
}

int Bullet::GetDamage()
{
	std::random_device rd;                          
	std::mt19937 gen(rd());                         
	std::uniform_int_distribution<int> distribution(m_minDamage, m_maxDamage);

	return distribution(gen);
}

void Bullet::Remove()
{
	m_isActive = false;
	m_weapon->ReleaseFromActivePool(this);
}
