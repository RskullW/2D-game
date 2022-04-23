#pragma once

#include <SDL2/SDL.h>
#include "string"
#include "startWindow.h"
#include "TextureManager.h"
#include "Game.h"
#include "soundGame.h"

class startWindow {
public:
    startWindow() {SDL_Log("start menu open");}
    startWindow(std::string textureID, int srcH, int srcW, int destH, int destW)
    {
        m_pTextureID = TextureManager::GetInstance()->getTexture(textureID);
        src.h = srcH;
        src.w = srcW;
        dest.h = destH;
        dest.w = destW;
        src.x = src.y = dest.x = dest.y = 0;
    }
    void draw() {
        soundGame::GetInstance()->playEffect("start_menu");

        while (timeStartWindow++ != 1000) {
            SDL_RenderClear(Game::GetInstance()->GetRenderer());
            SDL_RenderCopy(Game::GetInstance()->GetRenderer(), m_pTextureID, &src, &dest);
            SDL_RenderPresent(Game::GetInstance()->GetRenderer());
        }
    }
    ~startWindow() {SDL_Log("start menu closed");}

private:
    SDL_Texture* m_pTextureID;
    SDL_Rect src, dest;

    int timeStartWindow = 0;
};