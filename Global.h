#pragma once


struct WindowSettings
{
	int Width = 1366;
	int Height = 768;
};

inline WindowSettings g_WindowSettings;


namespace Tween
{
	enum TweenEase
	{
		LINEAR,
		IN_SIN,
		OUT_SIN,
		IN_OUT_SIN,
		IN_QUAD,
		OUT_QUAD,
		IN_OUT_QUAD,
		IN_CUBIC,
		OUT_CUBIC,
		IN_OUT_CUBIC,
		IN_QUART,
		OUT_QUART,
		IN_OUT_QUART,
		IN_QUINT,
		OUT_QUINT,
		IN_OUT_QUINT,
		IN_EXPO,
		OUT_EXPO,
		IN_OUT_EXPO,
		IN_CIRC,
		OUT_CIRC,
		IN_OUT_CIRC,
		IN_BACK,
		OUT_BACK,
		IN_OUT_BACK,
		IN_ELASTIC,
		OUT_ELASTIC,
		IN_OUT_ELASTIC,
		IN_BOUNCE,
		OUT_BOUNCE,
		IN_OUT_BOUNCE,
	};
}

namespace General
{
	enum Layer
	{
		DEFAULT = 1,
		PLAYER = 2,
		ENEMY = 4,
	};
	enum GameStateType
	{
		GAMEPLAY,
		ENDWAVE,
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
		LVL_UP_ICON,

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
		WEAPON = 2,
		ENEMY = 3,
		ITEM = 4,
		UI = 999,

		COUNT = 5,
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
