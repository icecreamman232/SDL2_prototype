#include "GameObject.h"
#include "Collider.h"
#include "Game.h"

GameObject::GameObject(const char* name,SDL_Texture* texture,int initX, int initY, int width, int height)
{
	m_name = name;

	m_texture = texture;
	m_pos.x = initX;
	m_pos.y = initY;
	m_angle = 0;

	m_srcRect.w = width;
	m_srcRect.h = height;
	m_srcRect.x = 0;
	m_srcRect.y = 0;

	m_destRect.x = m_pos.x;
	m_destRect.y = m_pos.y;
	m_destRect.w = m_srcRect.w * 3;
	m_destRect.h = m_srcRect.h * 3;

	m_collider = new Collider(this);

	//New game object created will be set to layer default
	SetLayer(Layer::DEFAULT);
	m_isActive = true;
}

GameObject::GameObject(const char* name, SDL_Texture* texture, int width, int height)
{
	m_name = name;

	m_texture = texture;
	m_pos.x = 0;
	m_pos.y = 0;
	m_angle = 0;

	m_srcRect.w = width;
	m_srcRect.h = height;
	m_srcRect.x = 0;
	m_srcRect.y = 0;

	m_destRect.x = m_pos.x;
	m_destRect.y = m_pos.y;
	m_destRect.w = m_srcRect.w * 3;
	m_destRect.h = m_srcRect.h * 3;

	m_collider = new Collider(this);

	//New game object created will be set to layer default
	SetLayer(Layer::DEFAULT);
	m_isActive = true;
}

void GameObject::Update(float deltaTime)
{
	if (!m_isActive) return;
	m_destRect.x = m_pos.x;
	m_destRect.y = m_pos.y;
	m_destRect.w = m_srcRect.w * 3;
	m_destRect.h = m_srcRect.h * 3;
}

void GameObject::Render()
{
	if (!m_isActive) return;
	SDL_RenderCopyExF(Game::Renderer, m_texture, &m_srcRect, &m_destRect,m_angle,NULL,SDL_FLIP_NONE);

}

void GameObject::SetPosition(int x, int y)
{
	m_pos.x = x;
	m_pos.y = y;
}

void GameObject::SetRotation(double angle)
{
	m_angle = angle;
}

void GameObject::LookAt(int x, int y)
{
	float relativeX = x - m_pos.x;
	float relativeY = y - m_pos.y;

	m_angle = SDL_atan2(relativeY, relativeX) * (180.0 / M_PI ) + 90;
	SetRotation(m_angle);
}

bool GameObject::IsCollideWith(GameObject* other)
{
	//If game object is inactive, it should not collide with any
	if (!m_isActive) return false;

	return m_collider->IsCollideWith(other);
}

void GameObject::SetLayer(Layer layer)
{
	LayerManager::Instance().SetLayer(this, layer);
}

const SDL_FRect GameObject::Rect()
{
	return m_destRect;
}



