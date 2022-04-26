#pragma once

#include <SDL2/SDL.h>
#include "string"
#include "startWindow.h"
#include "TextureManager.h"
#include "Game.h"
#include "soundGame.h"
#include "Nickname.h"

class startWindow {
public:
    startWindow() {SDL_Log("start menu open");}
    startWindow(std::string textureID, int srcH, int srcW, int destH, int destW)
    {
        m_pTextureID = TextureManager::GetInstance()->getTexture(textureID);
        pathString = textureID;
        src.h = srcH;
        src.w = srcW;
        dest.h = destH;
        dest.w = destW;
        src.x = src.y = dest.x = dest.y = 0;
    }
    void draw() {
        soundGame::GetInstance()->playEffect(pathString);

        while (timeStartWindow++ != 1000) {
            SDL_RenderClear(Game::GetInstance()->GetRenderer());
            SDL_RenderCopy(Game::GetInstance()->GetRenderer(), m_pTextureID, &src, &dest);
            SDL_RenderPresent(Game::GetInstance()->GetRenderer());
        }

        SDL_Texture* m_textureBackground = TextureManager::GetInstance()->getTexture("entername");
        SDL_Rect m_srcBackground;
        m_srcBackground.x = m_srcBackground.y = 0;
        m_srcBackground.w = SCREEN_WIDTH;
        m_srcBackground.h = SCREEN_HEIGHT;

        Nickname* enterNick = new Nickname("TimerText");

        while (enterNick->running()) {
            enterNick->Update();
            SDL_RenderClear(Game::GetInstance()->GetRenderer());
            SDL_RenderCopy(Game::GetInstance()->GetRenderer(), m_textureBackground, &m_srcBackground, &m_srcBackground);
            enterNick->Render();
            SDL_RenderPresent(Game::GetInstance()->GetRenderer());

        }

        delete enterNick;

    }
    ~startWindow() {SDL_Log("start menu closed");}

private:
    SDL_Texture* m_pTextureID;
    SDL_Rect src, dest;

    std::string pathString;
    int timeStartWindow = 0;
};