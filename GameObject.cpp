#include "GameObject.h"
#include "Game.h"
#include "Collider.h"
#include "Math/MathHelper.h"

int GameObject::s_nextID = 0;

GameObject::GameObject(const char* name, TEXTURE_ID textureID, float initX, float initY, int width, int height, int order)
{
	m_name = name;

	m_pos.x = initX;
	m_pos.y = initY;
	m_angle = 0;

	m_collider = new Collider(this);
	m_canCollide = true;

	m_sprite = new Sprite(AssetManager::Instance().LoadTexture(textureID), initX, initY, width, height, order);

	//New game object created will be set to layer default
	SetLayer(Layer::DEFAULT);
	m_id = s_nextID;
	s_nextID++;
	m_isActive = true;
}

GameObject::GameObject(const char* name, TEXTURE_ID textureID, int width, int height, int order)
{
	m_name = name;

	m_pos.x = 0;
	m_pos.y = 0;
	m_angle = 0;

	m_collider = new Collider(this);

	m_sprite = new Sprite(AssetManager::Instance().LoadTexture(textureID), m_pos.x, m_pos.y, width, height, order);

	//New game object created will be set to layer default
	SetLayer(Layer::DEFAULT);
	m_isActive = true;
}

GameObject::~GameObject()
{
	m_isActive = false;
	if (m_sprite != nullptr)
	{
		delete m_sprite;
	}
	if (m_collider != nullptr)
	{
		delete m_collider;
	}
}

void GameObject::Update(float deltaTime)
{
	if (!m_isActive) return;

	m_sprite->Update(m_pos.x, m_pos.y);
}

void GameObject::Render()
{
	if (!m_isActive) return;
	m_sprite->Render(m_angle);
}

void GameObject::SetPosition(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
}

void GameObject::SetRotation(float angle)
{
	m_angle = angle;
}

void GameObject::LookAt(int x, int y)
{
	float relativeX = x - m_pos.x;
	float relativeY = y - m_pos.y;

	m_angle = SDL_atan2f(relativeY, relativeX) * (180.0f / MathHelper::PI ) + 90.0f;
	SetRotation(m_angle);
}

bool GameObject::IsCollideWith(GameObject* other)
{
	//If game object is inactive, it should not collide with any
	if (!m_isActive) return false;

	if (!m_canCollide) return false;

	return m_collider->IsCollideWith(other);
}

void GameObject::SetLayer(Layer layer)
{
	m_layer = layer;
}

const SDL_FRect GameObject::Rect()
{
	return m_sprite->GetRect();
}

int GameObject::GetID()
{
	return m_id;
}




