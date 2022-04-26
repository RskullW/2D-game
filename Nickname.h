#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include "TextureManager.h"

class Nickname {
public:
    Nickname(std::string id);

    void Render();
    void Update();
    void Clean();
    bool HandleEvents();

    bool running() {return m_isActivated;}

    template<class T> void Log(T txt) {
        std::cout << "NICKNAME_LOG: " << txt << '\n';
    }

private:

    bool m_isActivated;
    unsigned short dt;
    int m_LengthNick;

    std::string m_textureID;
    std::string m_nickname;
    SDL_Texture* m_pTextureID;
    SDL_Surface* m_pSurface;
    TTF_Font* m_pFont;

    SDL_Texture* m_textureBackground;

    SDL_Rect m_srcBackground;
};
