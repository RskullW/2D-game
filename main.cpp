#include "Game.h"
#include "Timer.h"
#include "soundGame.h"
#include "startWindow.h"

int WinMain(int argc, char* argv[])
{
	Game::GetInstance()->init("Test game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

    startWindow* Start = new startWindow("startMenu", SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH);
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
	}

	Game::GetInstance()->clean();

	return 0;
}