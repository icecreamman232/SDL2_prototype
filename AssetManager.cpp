#include <SDL_image.h>

#include "AssetManager.h"
#include "Game.h"

void AssetManager::Initialize()
{
    m_texturePathList[PLAYER_TEX] = "Asset/blue-starship.png";
    m_texturePathList[SLIME_TEX] = "Asset/space-slime.png";
    m_texturePathList[WHITE_BAR_UI] = "Asset/white-bar.png";
    m_texturePathList[PLAYER_NORMAL_BULLET] = "Asset/normal-bullet.png";

}

const char* AssetManager::GetTexturePath(TEXTURE_ID textureID)
{
    return m_texturePathList[textureID];
}

SDL_Texture* AssetManager::LoadTexture(TEXTURE_ID textureID)
{
    SDL_Surface* surface = IMG_Load(GetTexturePath(textureID));
    m_textureList[textureID] = SDL_CreateTextureFromSurface(Game::Renderer, surface);
    SDL_FreeSurface(surface);
    return m_textureList[textureID];
}
