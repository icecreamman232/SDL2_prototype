#include "SpaceShip.h"
#include <iostream>
#include "Game.h"

SpaceShip::SpaceShip(const char* texturePath, SDL_Renderer* renderer, int initX, int initY)
	:GameObject(texturePath, renderer,initX, initY)
{
	m_direction.x = 0;
	m_direction.y = 0;
	m_moveSpeed = 200;
}

void SpaceShip::Update(float deltaTime)
{
	m_pos += m_direction * (m_moveSpeed * deltaTime);
	
	if (m_pos.x <= 0)
	{
		m_pos.x = 0;
	}
	else if (m_pos.x >= Game::ScreenWidth)
	{
		m_pos.x = Game::ScreenWidth;
	}

	if (m_pos.y <= 0)
	{
		m_pos.y = 0;
	}
	else if (m_pos.y >= Game::ScreenHeight)
	{
		m_pos.y = Game::ScreenHeight;
	}

	GameObject::Update(deltaTime);
}

void SpaceShip::SetDirectionX(float value)
{
	m_direction.x = value;
}

void SpaceShip::SetDirectionY(float value)
{
	m_direction.y = value;
}
