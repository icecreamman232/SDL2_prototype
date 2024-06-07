#include "UIImage.h"
#include "AssetManager.h"

UIImage::UIImage()
{
	m_sprite = nullptr;
	m_width = 0;
	m_height = 0;
}

void UIImage::Init(Render::TEXTURE_ID textureID, int x, int y, int width, int height)
{
	m_sprite = new Sprite(AssetManager::Instance().LoadTexture(textureID), x, y, width, height, 0);
	m_pos.x = x;
	m_pos.y = y;
	m_width = width;
	m_height = height;
}

void UIImage::Render()
{
	m_sprite->Render(0);
}

void UIImage::Update()
{
	m_sprite->Update(m_pos.x, m_pos.y);
}

void UIImage::SetPosition(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
}
