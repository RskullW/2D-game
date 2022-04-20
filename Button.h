#pragma once
#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "mouse.h"

struct buttonFile
{
    SDL_Texture* m_Texture;
    SDL_Rect src, dest;
};

class Button
{
public:
    Button() {}

    Button(std::string textureID, int srcH, int srcW, int destH, int destW)
    {

        m_Button.m_Texture = TextureManager::GetInstance()->getTexture(textureID);

        m_Button.src.h = srcH;
        m_Button.src.w = srcW;
        m_Button.src.x = 0;

        m_Button.dest.h = destH;
        m_Button.dest.w = destW;

    }

    void update(mouse& mse)
    {
        if (SDL_HasIntersection(&m_Button.dest, &mse.getPoint()))
        {
            m_isSelected = true;
            m_Button.src.x = m_Button.src.w;
        }

        else
        {
            m_isSelected = false;
            m_Button.src.x = 0;
        }
    }

    void draw(SDL_Renderer* m_pRendererButton)
    {
        SDL_RenderCopy(m_pRendererButton, m_Button.m_Texture, &m_Button.src, &m_Button.dest);
    }

    void clean()
    {
        SDL_DestroyTexture(m_Button.m_Texture);
    }

    SDL_Rect getSource() {return m_Button.src;}
    SDL_Rect getDest() {return m_Button.dest;}

    void setSourceX(int axisX) { m_Button.src.x = axisX; }
    void setSourceY(int axisY) { m_Button.src.y = axisY; }
    void setSourceW(int axisW) { m_Button.src.w = axisW; }
    void setSourceH(int axisH) { m_Button.src.h = axisH; }
    void setSource(SDL_Rect newSource) {m_Button.src = newSource;}

    void setDestX(int axisX) { m_Button.dest.x = axisX; }
    void setDestY(int axisY) { m_Button.dest.y = axisY; }
    void setDestW(int axisW) { m_Button.dest.w = axisW; }
    void setDestH(int axisH) { m_Button.dest.h = axisH; }
    void setDest(SDL_Rect newSource) {m_Button.dest = newSource;}

private:
    bool m_isSelected = false;
    buttonFile m_Button;
};