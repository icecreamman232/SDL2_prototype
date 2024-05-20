#pragma once
#include <map>
#include <SDL.h>

#include "Singleton.h"

enum TEXTURE_ID
{
	PLAYER_TEX,
	SLIME_TEX,
};

class AssetManager : public Singleton<AssetManager>
{
public:
	void Initialize();
	const char* GetTexturePath(TEXTURE_ID textureID);
	SDL_Texture* LoadTexture(TEXTURE_ID textureID);
private:
	std::map<TEXTURE_ID,const char*> m_texturePathList;
	std::map<TEXTURE_ID, SDL_Texture*> m_textureList;
};

