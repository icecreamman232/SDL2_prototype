#pragma once
#include "UIBase.h"
#include "Sprite.h"
#include "Math/Vector2.h"
#include "Global.h"


class UIImage : public UIBase
{
public:
	UIImage();
	void Init(Render::TEXTURE_ID textureID, int x, int y, int width, int heigh);
	void Render() override;
	void Update() override;
	void SetPosition(float x, float y);
	inline float GetPosX() { return m_pos.x; };
	inline float GetPosY() { return m_pos.y; };
	inline int GetWidth() { return m_width; };
	inline int GetHeight() { return m_height; };
	inline SDL_FRect* GetRect() { return m_sprite->GetRectPointer(); };
private:
	Sprite* m_sprite;
	Vector2 m_pos;
	int m_width;
	int m_height;

};

