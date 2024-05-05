#include "SpaceShip.h"
#include <iostream>
#include "Game.h"

SpaceShip::SpaceShip(const char* texturePath, SDL_Renderer* renderer, int initX, int initY)
	:GameObject(texturePath, renderer,initX, initY)
{
	m_directionX = 0;
	m_directionY = 0;
	m_moveSpeed = 200;
}

void SpaceShip::Update(float deltaTime)
{
	m_posX += m_directionX * (m_moveSpeed * deltaTime);
	m_posY += m_directionY * (m_moveSpeed * deltaTime);
	
	if (m_posX <= 0)
	{
		m_posX = 0;
	}
	else if (m_posX >= Game::ScreenWidth)
	{
		m_posX = Game::ScreenWidth;
	}

	if (m_posY <= 0)
	{
		m_posY = 0;
	}
	else if (m_posY >= Game::ScreenHeight)
	{
		m_posY = Game::ScreenHeight;
	}

	GameObject::Update(deltaTime);
}

void SpaceShip::SetDirectionX(float value)
{
	m_directionX = value;
}

void SpaceShip::SetDirectionY(float value)
{
	m_directionY = value;
}
