#pragma once
#include "UIBase.h"
#include "Selectable.h"
#include "Sprite.h"
#include "Math/Vector2.h"
#include "Global.h"


class UIImage : public UIBase, public Selectable
{
public:
	UIImage();
	virtual void Init(Render::TEXTURE_ID textureID, int x, int y, int width, int heigh, int spriteFrame = 0);
	void Render() override;
	virtual void Update() override;
	void SetPosition(float x, float y);
	void FillColor(SDL_Color color);
	inline float GetPosX() { return m_pos.x; };
	inline float GetPosY() { return m_pos.y; };
	inline int GetWidth() { return m_width; };
	inline int GetHeight() { return m_height; };
	inline SDL_FRect* GetRect() { return m_sprite->GetRectPointer(); };
protected:
	SDL_Color m_color;
	Sprite* m_sprite;
	Vector2 m_pos;
	int m_width;
	int m_height;

};

