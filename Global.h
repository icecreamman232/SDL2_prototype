#pragma once

namespace General
{
	enum Layer
	{
		DEFAULT = 0,
		PLAYER = 1,
		ENEMY = 2,
	};

}

namespace Render
{
	enum TEXTURE_ID
	{
		//SPRITE
		PLAYER_TEX,
		SLIME_TEX,

		//WEAPON
		PLAYER_NORMAL_BULLET = 50,

		//UI
		WHITE_BAR_UI = 100,
	};


	enum RenderLayer
	{
		DEFAULT = 0,
		PLAYER = 1,
		ENEMY = 2,
		UI = 999,
	};
}
