#include "Game.h"
#include "Timer.h"
#include "soundGame.h"
#include "startWindow.h"

int WinMain(int argc, char* argv[])
{
	Game::GetInstance()->init("Test game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

    startWindow* Start = new startWindow("start_menu", SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH);
    Start->draw();
    delete Start;

    soundGame::GetInstance()->playMusic("theme");
    while (Game::GetInstance()->running())
	{
		Game::GetInstance()->handleEvents();
		Game::GetInstance()->Update();
		Game::GetInstance()->renderer();
		Timer::GetInstance()->Tick();
        Game::GetInstance()->exitMenu();

        if (Game::GetInstance()->getFinish()==1)
        {
            break;
        }
	}

    if (Game::GetInstance()->getFinish()==1)
    {
        soundGame::GetInstance()->stopEffect(-1);
        soundGame::GetInstance()->stopMusic();

        startWindow* finishMenu = new startWindow("eralash_konec", SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH);
        finishMenu->draw();
        delete finishMenu;
    }

	Game::GetInstance()->clean();

	return 0;
}