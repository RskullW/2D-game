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
    m_buttonStart = new Button("start", 75, 285, 75, 285);
    m_buttonCredits = new Button("credits", 75, 285, 75, 285);
    m_buttonExit = new Button("exit", 75, 285, 75, 285);
    credits = new credits_menu("credits_menu",  640, 960, 640, 960);
    // Coordinates buttons
    coordinateButtons(m_buttonStart, 0, SCREEN_WIDTH/2 - m_buttonStart->getDest().w/2, 180);
    coordinateButtons(m_buttonCredits, 0, SCREEN_WIDTH/2 - m_buttonCredits->getDest().w/2, 285);
    coordinateButtons(m_buttonExit, 0, SCREEN_WIDTH/2 - m_buttonExit->getDest().w/2, 390);

    // Source and destination texture main menu

}

void menu::update(SDL_Renderer* m_pRenderer){

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
            credits->draw(m_pRenderer);
            SDL_Delay(5000);
            isCredits = true;
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
    SDL_ShowCursor(false);
    isActivated = false;
    SDL_DestroyTexture(m_pTexture);
}

void menu::coordinateButtons(Button* butUser, int srcY, int destX, int destY) {
    butUser->setSourceY(srcY);
    butUser->setDestX(destX);
    butUser->setDestY(destY);
}