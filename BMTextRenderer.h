#pragma once
#include "Global.h"
#include "Math/Vector2.h"
#include <string>
#include <SDL.h>
#include "UIBase.h"

using namespace Render;


class BMTextRenderer : public UIBase
{ 
public:
	void Initialize(TEXTURE_ID textureID, std::string text,
		Pivot pivot, float x, float y);
	void Render() override;

	inline void SetSpacing(float spacing) { m_spacing = spacing; };
	inline void SetSize(float size) { m_size = size; };
	inline void SetText(std::string newText) { m_text = newText; };

	inline float GetSpacing(int ascii) 
	{ 
		return ascii == 32 ? m_spacing/2 : m_spacing;
	};

private:

	void ComputeTextSize();
	float GetOffSetX();
	float GetOffSetY();

	const int m_startAsciiValue = 32;
	const int m_maxCol = 26;

	SDL_Texture* m_texture;
	SDL_Rect m_srcRect;
	SDL_FRect m_destRect;

	std::string m_text;

	Vector2 m_pos;
	Pivot m_pivot;

	float m_textSize = 0;
	float m_size = 16;
	float m_spacing = 16;
};

