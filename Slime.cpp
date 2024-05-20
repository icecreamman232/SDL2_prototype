#include "Slime.h"
#include "Game.h"

Slime::Slime(int id,const char* name, SDL_Texture* texture, 
	int initX, int initY, int width, int height) 
	: GameObject(name, texture,initX, initY, width, height)
{
	m_id = id;
	std::random_device rd;
	std::mt19937 randomGenerator(rd() + m_id);  // Mersenne Twister random number engine

	GetNextDirection(m_direction);
	m_moveSpeed = 150;

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
	else if (m_pos.x >= Game::ScreenWidth - m_destRect.w)
	{
		m_pos.x = Game::ScreenWidth - m_destRect.w;
		GetNextDirection(m_direction);
	}

	if (m_pos.y <= 0)
	{
		m_pos.y = 0;
		GetNextDirection(m_direction);
	}
	else if (m_pos.y >= Game::ScreenHeight - m_destRect.h)
	{
		m_pos.y = Game::ScreenHeight - m_destRect.h;
		GetNextDirection(m_direction);
	}

	GameObject::Update(deltaTime);
}

void Slime::GetNextDirection(Vector2& direction)
{
	std::uniform_real_distribution<float> dist(-1.0, 1.0);
	direction.x = dist(randomGenerator);
	direction.y = dist(randomGenerator);
}
