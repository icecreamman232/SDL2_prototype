#pragma once
#include <map>
#include <SDL.h>

#include "Singleton.h"
#include "Global.h"
#include <utility>

using namespace Render;

struct TextAtlas
{
	Uint16 ASCII;
	Uint16 XCoord;
	Uint16 YCoord;
	Uint16 Width;
	Uint16 Height;
};

class AssetManager : public Singleton<AssetManager>
{
public:
	void Initialize();
	const char* GetTexturePath(TEXTURE_ID textureID);
	SDL_Texture* LoadTexture(TEXTURE_ID textureID,bool isFontTexture=false);
	SDL_Texture* GetTexture(TEXTURE_ID textureID, bool isFontTexture = false);

	TextAtlas GetCharacterInfo(Uint16 asciii);
private:
	std::map<TEXTURE_ID,const char*> m_texturePathList;
	std::map<TEXTURE_ID, SDL_Texture*> m_textureList;
	std::map<Uint16, TextAtlas> m_fontAtlas;
	SDL_Surface* m_fontSurface;
	Uint32* m_fontPixel;

	Uint32 GetPixelAt(int x, int y);
	SDL_Color GetColorPixelAt(int x, int y);
	std::pair<int,int> GetLeftEdgeOfBitmapChar(SDL_Color bgColor,int startX, int startY, int maxX, int maxY);
	std::pair<int, int> GetRightEdgeOfBitmapChar(SDL_Color bgColor, int startX, int startY, int maxX, int maxY);
	std::pair<int, int> GetTopEdgeOfBitmapChar(SDL_Color bgColor, int startX, int startY, int maxX, int maxY);
	std::pair<int, int> GetBotEdgeOfBitmapChar(SDL_Color	 bgColor, int startX, int startY, int maxX, int maxY);
};



