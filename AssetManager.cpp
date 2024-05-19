#include "AssetManager.h"

void AssetManager::Initialize()
{
    m_texturePathList[PLAYER_TEX] = "Asset/blue-starship.png";
    m_texturePathList[SLIME_TEX] = "Asset/space-slime.png";

}

const char* AssetManager::GetTexturePath(TEXTURE_ID textureID)
{
    return m_texturePathList[textureID];
}
