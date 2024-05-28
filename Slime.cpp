#include "Slime.h"
#include "Game.h"
#include "EnemyHealthEventDispatcher.h"
#include "XPEventDispatcher.h"

Slime::Slime(const char* name, TEXTURE_ID textureID, 
	int initX, int initY, int width, int height, int order) 
	: GameObject(name, textureID,initX, initY, width, height, order)
{
	GetNextDirection(m_direction);

	m_moveSpeed = 150;
	m_minDamage = 5;
	m_maxDamage = 10;
	m_health = new Health();
	m_health->Initialize(10, 0.5);

	m_idleAnim = new Animation(SLIME_TEX, m_sprite, 1, 0.1, 16, 16);
	m_deadAnim = new Animation(ENEMY_EXPLOSION, m_sprite, 5, 0.1, 16, 16);

	m_deadSFX = Mix_LoadWAV("Asset/Sound/enemy-pop-out-death.wav");

	m_canCollide = true;
	m_canMove = true;
}

Slime::~Slime()
{
	Mix_FreeChunk(m_deadSFX);
	GameObject::~GameObject();
}

void Slime::Update(float deltaTime)
{
	UpdateMovement(deltaTime);
	
	m_deadAnim->Update(deltaTime);

	//Once everything's finished, we move Slime from scene
	if (m_deadAnim->IsFinished() 
		&& m_health->GetCurrentHealth() <= 0
		&& !m_canMove)
	{
		//EnemyHealthEventDispatcher::Trigger(EnemyHealthEvent{ true , m_id});
		m_isActive = false;
		Game::CurrentScene->Remove(this, RenderLayer::ENEMY);
	}

	GameObject::Update(deltaTime);
}

void Slime::UpdateMovement(float deltaTime)
{
	if (m_canMove)
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
	}
}

void Slime::TakeDamage(int damage)
{
	if(!m_isActive) return;

	if (!m_canCollide) return;

	if (m_health->GetCurrentHealth() <= 0) return;

	if (m_health == nullptr) return;

	m_health->TakeDamage(damage);

	//Slime's dead, play dead anim
	if (m_health->GetCurrentHealth() <= 0)
	{
		m_canMove = false;
		Mix_PlayChannel(-1, m_deadSFX, 0);
		m_deadAnim->Play();
		m_canCollide = false;
		XPEventDispatcher::Trigger(XPEvent{ 10 });
	}
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
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(-1.0, 1.0);
	direction.x = dist(gen);
	direction.y = dist(gen);
}


