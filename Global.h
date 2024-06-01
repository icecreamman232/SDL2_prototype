#pragma once


struct WindowSettings
{
	int Width = 1366;
	int Height = 768;
};

inline WindowSettings g_WindowSettings;

namespace General
{
	enum Layer
	{
		DEFAULT = 1,
		PLAYER = 2,
		ENEMY = 4,
	};

}

namespace Render
{
	enum TEXTURE_ID
	{
		//SPRITE
		PLAYER_TEX,
		SLIME_TEX,
		ENEMY_EXPLOSION,
		COIN,

		//WEAPON
		PLAYER_NORMAL_BULLET = 50,

		//UI
		WHITE_BAR_UI = 100,

		//BITMAP FONT
		BM_FONT_PIXEL = 300,
	};


	enum RenderLayer
	{
		DEFAULT = 0,
		PLAYER = 1,
		ENEMY = 2,
		ITEM = 3,
		UI = 999,

		COUNT = 4,
	};

	enum Pivot
	{
		LEFT,
		RIGHT,
		CENTER,
		TOP,
		BOTTOM,
	};
}
