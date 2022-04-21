#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "TextureManager.h"

class credits_menu
{
public:
    credits_menu(std::string textureID, int srcH, int srcW, int destH, int destW)
    {
        m_pTextureID = TextureManager::GetInstance()->getTexture(textureID);
        src.h = srcH;
        src.w = srcW;
        dest.h = destH;
        dest.w = destW;
        src.x = src.y = dest.x = dest.y = 0;
    }
    void draw(SDL_Renderer* m_pRenderer)
    {
        SDL_RenderClear(m_pRenderer);
        SDL_SetRenderDrawColor(m_pRenderer, 0,0,0,0);

        SDL_RenderCopy(m_pRenderer, m_pTextureID, &src, &dest);

        SDL_RenderPresent(m_pRenderer);
    }
    void clean(){
        SDL_DestroyTexture(m_pTextureID);
    }
private:
    SDL_Texture* m_pTextureID;
    SDL_Rect src, dest;
};