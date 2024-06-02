#include "IItem.h"
#include "Collider.h"

int IItem::s_nextID = 0;

IItem::IItem()
{
	m_isInitialized = false;
}

void IItem::Initialize(const char* name, TEXTURE_ID textureID, float initX, float initY, int width, int height, int order)
{
	m_isActive = true;

	m_pos.x = initX;
	m_pos.y = initY;
	m_angle = 0;

	SetLayer(Layer::DEFAULT);


	m_isPickedUp = false;

	m_canCollide = true;

	if (!m_isInitialized)
	{
		m_name = name;
		m_collider = new Collider(this);
		m_sprite = new Sprite(AssetManager::Instance().LoadTexture(textureID), initX, initY, width, height, order);
		m_id = s_nextID;
		s_nextID++;
		m_isInitialized = true;
	}
}

void IItem::PickedUp()
{
	m_isPickedUp = true;
}
