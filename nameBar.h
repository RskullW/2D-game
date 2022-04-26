#pragma once
#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
#include "Game.h"
#include "Camera.h"
#include "FontsManager.h"

class Namebar {
public:
    Namebar(std::string name): nickname(name) {
        color.r = color.g = color.b = 255;
        color.a = 125;
    };


    void Draw(int x, int y) {
        src.x = x;
        src.y = y;

        m_pSurface = TTF_RenderText_Solid(FontsManager::GetInstance()->GetFont("TimerText"), nickname.c_str(), color);

        if (m_pSurface == nullptr){
            SDL_Log("Error! Font do not exist, surface not loaded...");
        }

        m_pTexture = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), m_pSurface);

        if (m_pTexture==nullptr){
            SDL_Log("Error! Font do not exist, texture not loaded...");
        }
        SDL_FreeSurface(m_pSurface);

        SDL_QueryTexture(m_pTexture, NULL, NULL, &src.w, &src.h);

        src.w/=2;
        src.h/=2;

        SDL_RenderCopy(Game::GetInstance()->GetRenderer(), m_pTexture, NULL, &src);
    }

    void Clean() {
        SDL_DestroyTexture(m_pTexture);
    }
private:
    std::string nickname;

    SDL_Rect src;
    SDL_Color color;

    SDL_Texture* m_pTexture;
    SDL_Surface* m_pSurface;
};