#pragma once
#include <SDL.h>
#include "Math/Vector2.h"

class Sprite
{
public:
	Sprite(SDL_Texture* texture, int x, int y, int width, int height, int order = 0);
	void Render(float angle);
	void Update(int x, int y);
	SDL_FRect GetRect();
	void SetFrame(int index);
	void SetTexture(SDL_Texture* newTexture);

	inline int GetOrder() { return m_order; };
private:
	//Rendering order
	int m_order;
	int m_width;
	int m_height;
	SDL_Texture* m_texture;
	SDL_Rect m_srcRect;
	SDL_FRect m_destRect;
};

