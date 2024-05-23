#include "Slime.h"
#include "Game.h"

Slime::Slime(const char* name, TEXTURE_ID textureID, 
	int initX, int initY, int width, int height, int order) 
	: GameObject(name, textureID,initX, initY, width, height, order)
{
	GetNextDirection(m_direction);
	std::cout << m_direction.x << "/" << m_direction.y << std::endl;

	m_moveSpeed = 150;
	m_minDamage = 5;
	m_maxDamage = 10;
	m_health = new Health();
	m_health->Initialize(10, 0.5);
	m_deadAnim = new Animation(ENEMY_EXPLOSION, m_sprite, 5, 0.1, 16, 16);
}

void Slime::Update(float deltaTime)
{
	//return; //TEMP TO DEBUG STOP SLIME MOVING
	m_pos += m_direction * (m_moveSpeed * deltaTime);

	//Check limit
	if (m_pos.x <= 0)
	{
		m_pos.x = 0;
		GetNextDirection(m_direction);
	}
	else if (m_pos.x >= Game::ScreenWidth - m_sprite->GetRect().w)
	{
		m_pos.x = Game::ScreenWidth - m_sprite->GetRect().w;
		GetNextDirection(m_direction);
	}

	if (m_pos.y <= 0)
	{
		m_pos.y = 0;
		GetNextDirection(m_direction);
	}
	else if (m_pos.y >= Game::ScreenHeight - m_sprite->GetRect().h)
	{
		m_pos.y = Game::ScreenHeight - m_sprite->GetRect().h;
		GetNextDirection(m_direction);
	}
	m_deadAnim->Update(deltaTime);
	GameObject::Update(deltaTime);
}

void Slime::TakeDamage(int damage)
{
	if(!m_isActive) return;
	if (m_health == nullptr) return;
	m_health->TakeDamage(damage);
	m_deadAnim->Play();

	//TEST ANIMATION
	//if (m_health->GetCurrentHealth() <= 0)
	//{
	//	m_isActive = false;
	//	//TODO: Implement death behavior and try to move/delete object from scene
	//	Game::CurrentScene->Remove(this,RenderLayer::ENEMY);
	//}
}

int Slime::GetDamage()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(m_minDamage, m_maxDamage);

	return distribution(gen);
}

void Slime::GetNextDirection(Vector2& direction)
{
	std::uniform_real_distribution<float> dist(-1.0, 1.0);
	direction.x = dist(randomGenerator);
	direction.y = dist(randomGenerator);
}
