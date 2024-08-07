#include "UIImage.h"
#include "AssetManager.h"

UIImage::UIImage()
{
	m_sprite = nullptr;
	m_width = 0;
	m_height = 0;
}

UIImage::~UIImage()
{
	m_sprite = nullptr;
}

void UIImage::Init(std::string name, Render::TEXTURE_ID textureID, int x, int y, int width, int height,int spriteFrame)
{
	m_name = name;
	m_sprite = new Sprite(AssetManager::Instance().LoadTexture(textureID), x, y, width, height, 0, true);
	m_sprite->SetFrame(spriteFrame);
	m_pos.x = x;
	m_pos.y = y;
	m_width = width;
	m_height = height;

	m_id = s_next_UIID;
	s_next_UIID++;
}

void UIImage::Render()
{
	if (!m_isActive) return;

	if (m_sprite == nullptr)
	{
		return;
	}
	m_sprite->Render(0);
}

void UIImage::Update()
{
	if (!m_isActive) return;
	m_sprite->Update(m_pos.x, m_pos.y);
}

void UIImage::SetPosition(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
}

void UIImage::FillColor(SDL_Color color)
{
	m_color = color;
	m_sprite->TintColor(m_color.r, m_color.g, m_color.b, m_color.a);
}
