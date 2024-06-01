#pragma once
#include "UIBase.h"
#include "Sprite.h"
#include "Math/Vector2.h"
#include "Global.h"


class UIImage : public UIBase, public Sprite
{
public:
	UIImage();
	void Init(Render::TEXTURE_ID textureID, int x, int y, int width, int heigh);
	void Render() override;
	void Update() override;
private:
	Sprite* m_sprite;
	Vector2 m_pos;
	int m_width;
	int m_height;

};

