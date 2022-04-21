#pragma once
#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "mouse.h"

class Button
{
public:
    Button() {}

    Button(std::string textureID, int srcH, int srcW, int destH, int destW)
    {

        m_Texture = TextureManager::GetInstance()->getTexture(textureID);

        src.h = srcH;
        src.w = srcW;
        src.x = 0;

        dest.h = destH;
        dest.w = destW;

    }

    void update(mouse& mse)
    {
        if (SDL_HasIntersection(&dest, &mse.getPoint()))
        {
            m_isSelected = true;
            src.x = src.w;
        }

        else
        {
            m_isSelected = false;
            src.x = 0;
        }
    }

    void draw(SDL_Renderer* m_pRendererButton)
    {
        SDL_RenderCopy(m_pRendererButton, m_Texture, &src, &dest);
    }

    void clean()
    {
        SDL_DestroyTexture(m_Texture);
    }

    void nullButton()
    {
        m_Texture = nullptr;
    }

    SDL_Rect getSource() {return src;}
    SDL_Rect getDest() {return dest;}
    SDL_Texture* getTexture() {return m_Texture;}

    void setSourceX(int axisX) { src.x = axisX; }
    void setSourceY(int axisY) { src.y = axisY; }
    void setSourceW(int axisW) { src.w = axisW; }
    void setSourceH(int axisH) { src.h = axisH; }
    void setSource(SDL_Rect newSource) {src = newSource;}

    void setDestX(int axisX) { dest.x = axisX; }
    void setDestY(int axisY) { dest.y = axisY; }
    void setDestW(int axisW) { dest.w = axisW; }
    void setDestH(int axisH) { dest.h = axisH; }
    void setDest(SDL_Rect newSource) {dest = newSource;}

    bool getSelected() {return m_isSelected;}
private:
    bool m_isSelected = false;
    SDL_Texture* m_Texture;
    SDL_Rect src, dest;
};