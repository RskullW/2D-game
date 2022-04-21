#include "menu.h"
#include "Game.h"
#include "input.h"

void menu::init(){
    Log("initialization menu");
    // isActivated || menu activated - true, else - false;
    isActivated = true;
    // zeroing variables
    isStart = isCredits = isExit = false;
    // Init cursor
    cursor = new mouse("cursor");
    // Init button
    m_buttonStart = new Button("start", 100, 380, 100, 380);
    m_buttonCredits = new Button("credits", 100, 380, 100, 380);
    m_buttonExit = new Button("exit", 100, 380, 100, 380);
    // Coordinates buttons
    coordinateButtons(m_buttonStart, 0, SCREEN_WIDTH/2 - m_buttonStart->getDest().w/2, 120);
    coordinateButtons(m_buttonCredits, 0, SCREEN_WIDTH/2 - m_buttonCredits->getDest().w/2, 300);
    coordinateButtons(m_buttonExit, 0, SCREEN_WIDTH/2 - m_buttonExit->getDest().w/2, 480);

    // Source and destination texture main menu

}

void menu::update(){

    m_buttonStart->update(*cursor);
    m_buttonCredits->update(*cursor);
    m_buttonExit->update(*cursor);
    cursor->update();

    if (input::GetInstance()->GetMouseButton() == true )
    {
        if (m_buttonStart->getSelected() == true)
        {
            isActivated = false;
            isStart = true;
        }

        else if (m_buttonCredits->getSelected() == true)
        {
            isActivated = false;
            isStart = true;
        }

        else if (m_buttonExit->getSelected() == true)
        {
            isActivated = false;
            isExit = true;
        }

        else
        {
            isStart = isCredits = isExit = false;
        }
    }
}

void menu::draw(SDL_Renderer* m_pRendererMenu){
    SDL_RenderClear(m_pRendererMenu);
    SDL_SetRenderDrawColor(m_pRendererMenu, 0, 0, 0, 0);

    SDL_RenderCopy(m_pRendererMenu, m_pTexture, &srcMainMenu, &destMainMenu);

    m_buttonStart->draw(m_pRendererMenu);
    m_buttonCredits->draw(m_pRendererMenu);
    m_buttonExit->draw(m_pRendererMenu);

    cursor->draw(m_pRendererMenu);

    SDL_RenderPresent(m_pRendererMenu);
}

void menu::clean() {
    // clean textures button from window game
    delete m_buttonStart;
    delete m_buttonCredits;
    delete m_buttonExit;
    delete cursor;
    // removing from the window game
    SDL_ShowCursor(false);

    isActivated = false;
}

void menu::coordinateButtons(Button* butUser, int srcY, int destX, int destY) {
    butUser->setSourceY(srcY);
    butUser->setDestX(destX);
    butUser->setDestY(destY);
}