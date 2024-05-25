#pragma once

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
		UI = 999,

		COUNT = 3,
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
