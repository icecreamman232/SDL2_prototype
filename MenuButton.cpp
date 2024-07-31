#include "MenuButton.h"
#include "Game.h"

void MenuButton::Init(std::string name, Render::TEXTURE_ID textureID, int x, int y, int width, int height, int spriteFrame)
{
	InitSelectable(x, y, width, height);
	UIImage::Init(name, textureID, x, y, width, height, spriteFrame);

	m_btnText.Initialize(Render::TEXTURE_ID::BM_FONT_PIXEL,
		name, Render::Pivot::CENTER, x, y);
	m_btnText.SetSpacing(0);
	m_btnText.SetSize(16);

	Game::CurrentScene->Add(this);
	Game::CurrentScene->Add(&m_btnText);
	m_shouldUpdate = true;
}

void MenuButton::CleanUp()
{
	m_shouldUpdate = false;

	Game::CurrentScene->Remove(this);
	Game::CurrentScene->Remove(&m_btnText);
	m_callback = nullptr;
}

void MenuButton::Update()
{
	if (!m_shouldUpdate) return;
	UpdateSelectable();
	m_btnText.Update();
}

void MenuButton::OnMouseLeftClick()
{
	if (m_callback)
	{
		m_callback();
	}
}

void MenuButton::SetButtonTextSize(float size)
{
	m_btnText.SetSize(size);
}

void MenuButton::SetButtonTextSpacing(float spacing)
{
	m_btnText.SetSpacing(spacing);
}

void MenuButton::SetTextPosition(float x, float y)
{
	m_btnText.SetPosition(x, y);
}

void MenuButton::SetCallBack(CallbackFunction callback)
{
	m_callback = callback;
}

