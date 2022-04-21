#pragma once
#include <iostream>
#include "Button.h"
#include "TextureManager.h"
#include "credits_menu.h"

class menu
{
public:
    menu() {Log("menu was created");}

    menu(std::string textureID, int srcH, int srcW, int destH, int destW)
    {
        m_pTexture = TextureManager::GetInstance()->getTexture(textureID);
        srcMainMenu.h = srcH;
        srcMainMenu.w = srcW;
        destMainMenu.h = destH;
        destMainMenu.w = destW;
        srcMainMenu.x = srcMainMenu.y = destMainMenu.x = destMainMenu.y = 0;
    }
    void init();

    void update(SDL_Renderer* m_pRenderer);
    void draw(SDL_Renderer* m_pRenderer);
    void clean();

    void setActive(bool broadfastUser) {isActivated = broadfastUser;}
    void setDefault() {isStart = isCredits = isExit = false;}

    void deleteButton()
    {
        // clean textures button from window game
        delete m_buttonStart;
        delete m_buttonCredits;
        delete m_buttonExit;
        delete cursor;
        // removing from the window game
        SDL_ShowCursor(false);

        isActivated = false;
    }

    bool getStart() {return isStart;}
    bool getCredits() {return isCredits;}
    bool getExit() {return isExit;}

    bool getActive() {return isActivated;}

public:
    template<class T>
    void Log(T str) {std::cout << "INFO_MENU: " << str << '\n';}

private:
    void coordinateButtons(Button* butUser, int srcY, int destX, int destY);

    bool isActivated;
    bool isStart, isCredits = false, isExit = false;

    Button* m_buttonStart, *m_buttonCredits, *m_buttonExit;
    mouse* cursor;
    credits_menu* credits;

    SDL_Texture* m_pTexture;
    SDL_Rect srcMainMenu, destMainMenu;

};