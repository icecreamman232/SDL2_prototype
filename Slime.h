#pragma once
#include "GameObject.h"

class Slime : public GameObject
{
public:
	Slime(const char* name, const char* texturePath, SDL_Renderer* renderer,
		int initX, int initY, int width, int height);
private:
};

