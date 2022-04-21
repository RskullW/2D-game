#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "TextureManager.h"

class mouse {
public:
    mouse(){}

    mouse(std::string textureID)
    {
        m_pTexture = TextureManager::GetInstance()->getTexture(textureID);
        Log(m_pTexture);
        rect.w = rect.h = 15;
        point.w = point.h = 1;

        SDL_ShowCursor(false);
    }

    SDL_Rect& getPoint() {return point;}

    void update()
    {
        SDL_GetMouseState(&rect.x, &rect.y);
        point.x = rect.x;
        point.y = rect.y;
    }
    void draw(SDL_Renderer* m_pRendererMouse)
    {
        SDL_RenderCopy(m_pRendererMouse, m_pTexture, nullptr, &rect);
    }
    void clean()
    {
        SDL_DestroyTexture(m_pTexture);
    }

    template <typename T>
    void Log(T str)
    {
        std::cout << "INFO: " << str << '\n';
    }

public:
    SDL_Texture* m_pTexture;
    SDL_Rect rect, point;
};
