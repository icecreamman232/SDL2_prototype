#pragma once
#include <SDL.h>
#include "Global.h"
#include "Sprite.h"

using namespace Render;

class Animation
{
public:
	Animation(TEXTURE_ID textureID, Sprite* sprite,int numberFrame,float timeFrame, int widthFrame, int heightFrame);
	void Play();
	void Update(float deltaTime);
	inline bool IsFinished() { return m_isFinished; };
private:
	SDL_Texture* m_texture;
	Sprite* m_sprite;

	bool m_isPlaying;
	bool m_isFinished;
	int m_widthFrame;
	int m_heightFrame;
	int m_numFrame;
	int m_curFrame;

	float m_timeFrame;
	float m_timer;
};

