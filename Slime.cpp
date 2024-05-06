#include "Slime.h"

Slime::Slime(const char* name, const char* texturePath, SDL_Renderer* renderer, 
	int initX, int initY, int width, int height) : GameObject(name, texturePath, renderer,initX, initY, width, height)
{

}
