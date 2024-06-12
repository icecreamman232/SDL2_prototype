#pragma once
#include <SDL.h>

class Sprite
{
public:
	Sprite(SDL_Texture* texture, float x, float y, int width, int height, int order = 0, bool isUI = false);
	void Render(float angle);
	void Update(float x, float y);
	SDL_FRect GetRect();
	SDL_FRect* GetRectPointer();
	void SetFrame(int index);
	void SetTexture(SDL_Texture* newTexture);
	void TintColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void ResetColor();

	inline SDL_Color GetColor() { return m_tintColor; };
	inline int GetOrder() { return m_order; };
private:

	bool m_isUI;

	//Rendering order
	int m_order;

	SDL_Color m_originalColor;
	SDL_Color m_tintColor;

	Uint8 m_originalAlpha;
	Uint8 m_curAlpha;

	int m_width;
	int m_height;
	SDL_Texture* m_texture;
	SDL_Rect m_srcRect;
	SDL_FRect m_destRect;
};

