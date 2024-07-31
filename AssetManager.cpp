#include <SDL_image.h>

#include "AssetManager.h"
#include "Game.h"

void AssetManager::Initialize()
{
    m_texturePathList[PLAYER_TEX] = "Asset/blue-starship.png";
    m_texturePathList[SLIME_TEX] = "Asset/space-slime.png";
    m_texturePathList[WHITE_BAR_UI] = "Asset/white-bar.png";
    m_texturePathList[ENEMY_EXPLOSION] = "Asset/enemy-die-explosion.png";
    m_texturePathList[PLAYER_NORMAL_BULLET] = "Asset/normal-bullet.png";
    m_texturePathList[COIN] = "Asset/coin.png";
    m_texturePathList[POWERUP_ICON] = "Asset/Powerup-icon/powerup-icon.png";
    m_texturePathList[LVL_UP_ICON] = "Asset/lvl-up-icon.png";
    m_texturePathList[BM_FONT_PIXEL] = "Asset/Font/pixel-sdl-font.bmp";

    LoadTexture(TEXTURE_ID::PLAYER_TEX);
    LoadTexture(TEXTURE_ID::SLIME_TEX);
    LoadTexture(TEXTURE_ID::WHITE_BAR_UI);
    LoadTexture(TEXTURE_ID::ENEMY_EXPLOSION);
    LoadTexture(TEXTURE_ID::PLAYER_NORMAL_BULLET);
    LoadTexture(TEXTURE_ID::COIN);
    LoadTexture(TEXTURE_ID::POWERUP_ICON);
    LoadTexture(TEXTURE_ID::LVL_UP_ICON);
    LoadTexture(TEXTURE_ID::BM_FONT_PIXEL, true);

    SDL_Color bgColor = GetColorPixelAt(0, 0);
    auto maxCol = 26; //Depends on the bmp texture format
    auto startAsciiVal = 32;
    for (size_t i = 33; i < 123; i++) //122 is last = "z"
    {
        auto index = i - startAsciiVal;
        auto originalX = (index - ((index / maxCol) * maxCol)) * 16;
        auto originalY = index / maxCol * 16;
        auto maxX = originalX + 16;
        auto maxY = originalY + 16;

        auto left = GetLeftEdgeOfBitmapChar(bgColor, originalX, originalY, maxX, maxY);
        auto right = GetRightEdgeOfBitmapChar(bgColor, originalX, originalY, maxX, maxY);
        auto top = GetTopEdgeOfBitmapChar(bgColor, originalX, originalY, maxX, maxY);
        auto bot = GetBotEdgeOfBitmapChar(bgColor, originalX, originalY, maxX, maxY);
       

        if (left == make_pair(-1,-1) || right == make_pair(-1, -1) || top == make_pair(-1, -1) || bot == make_pair(-1, -1))
        {
            continue;
        }
            
        auto width = right.first - left.first + 1;
        auto height = bot.second - top.second + 1;

        m_fontAtlas.insert(make_pair<Uint16, TextAtlas>
                (i, TextAtlas
                    {
                        (Uint16)i,
                        (Uint16)left.first,
                        (Uint16)top.second,
                        (Uint16)width,
                        (Uint16)height,
                    }));
    }
}

const char* AssetManager::GetTexturePath(TEXTURE_ID textureID)
{
    return m_texturePathList[textureID];
}

SDL_Texture* AssetManager::LoadTexture(TEXTURE_ID textureID, bool isFontTexture)
{
    SDL_Surface* surface = IMG_Load(GetTexturePath(textureID));
    if (isFontTexture)
    {
        m_fontSurface = SDL_ConvertSurfaceFormat(surface,SDL_PIXELFORMAT_ABGR8888,0);
        m_fontPixel = static_cast<Uint32*>(m_fontSurface->pixels);
    }
    m_textureList[textureID] = SDL_CreateTextureFromSurface(Game::Renderer, surface);
    SDL_SetTextureScaleMode(m_textureList[textureID], SDL_ScaleModeNearest);
    SDL_FreeSurface(surface);
    return m_textureList[textureID];
}

SDL_Texture* AssetManager::GetTexture(TEXTURE_ID textureID, bool isFontTexture)
{
    return m_textureList[textureID];
}

TextAtlas AssetManager::GetCharacterInfo(Uint16 asciii)
{
    return m_fontAtlas[asciii];
}

Uint32 AssetManager::GetPixelAt(int x, int y)
{
    return m_fontPixel[(y * m_fontSurface->pitch/4) + x];
}

SDL_Color AssetManager::GetColorPixelAt(int x, int y)
{
    SDL_Color color = { 0, 0, 0, 0 };

    if (x >= 0 && x < m_fontSurface->w && y >= 0 && y < m_fontSurface->h) 
    {
        Uint32* pixel = (Uint32*)((Uint8*)m_fontSurface->pixels + y * m_fontSurface->pitch + x * m_fontSurface->format->BytesPerPixel);

        SDL_GetRGBA(*pixel, m_fontSurface->format, &color.r, &color.g, &color.b, &color.a);
    }

    return color;
}

std::pair<int, int> AssetManager::GetLeftEdgeOfBitmapChar(SDL_Color bgColor, int startX, int startY, int maxX, int maxY)
{
    SDL_Color cacheColor;
    for (int x = startX; x < maxX; x++)
    {
        for (int y = startY; y < maxY; y++)
        {
            cacheColor = GetColorPixelAt(x, y);
            if (cacheColor.r != bgColor.r && cacheColor.g != bgColor.g 
                && cacheColor.b != bgColor.b && cacheColor.a!= bgColor.a)
            {
                return make_pair(x, y);
            }
        }
    }
    return make_pair(-1, -1);
}


std::pair<int, int> AssetManager::GetRightEdgeOfBitmapChar(SDL_Color bgColor, int startX, int startY, int maxX, int maxY)
{
    SDL_Color cacheColor;
    for (int x = maxX; x >= startX; x--)
    {
        for (int y = startY; y < maxY; y++)
        {
            cacheColor = GetColorPixelAt(x, y);
            if (cacheColor.r != bgColor.r && cacheColor.g != bgColor.g
                && cacheColor.b != bgColor.b && cacheColor.a != bgColor.a)
            {
                return make_pair(x, y);
            }
        }
    }
    return make_pair(-1, -1);
}

std::pair<int, int> AssetManager::GetTopEdgeOfBitmapChar(SDL_Color bgColor, int startX, int startY, int maxX, int maxY)
{
    SDL_Color cacheColor;
    for (int y = startY; y < maxY; y++)
    {
        for (int x = startX; x < maxX; x++)
        {
            cacheColor = GetColorPixelAt(x, y);
            if (cacheColor.r != bgColor.r && cacheColor.g != bgColor.g
                && cacheColor.b != bgColor.b && cacheColor.a != bgColor.a)
            {
                return make_pair(x, y);
            }
        }
    }
    return make_pair(-1, -1);
}

std::pair<int, int> AssetManager::GetBotEdgeOfBitmapChar(SDL_Color bgColor, int startX, int startY, int maxX, int maxY)
{
    SDL_Color cacheColor;
    for (int y = maxY; y >= startY; y--)
    {
        for (int x = startX; x < maxX; x++)
        {
            cacheColor = GetColorPixelAt(x, y);
            if (cacheColor.r != bgColor.r && cacheColor.g != bgColor.g
                && cacheColor.b != bgColor.b && cacheColor.a != bgColor.a)
            {
                return make_pair(x, y);
            }
        }
    }
    return make_pair(-1, -1);
}
