#pragma once
#include "Singleton.h"
#include <map>

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
private:
	std::map<TEXTURE_ID,const char*> m_texturePathList;
};

