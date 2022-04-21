#include "Game.h"
#include "Timer.h"

int WinMain(int argc, char* argv[])
{
	Game::GetInstance()->init("Test game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

	while (Game::GetInstance()->running())
	{
		Game::GetInstance()->handleEvents();
		Game::GetInstance()->Update();
		Game::GetInstance()->renderer();
		Timer::GetInstance()->Tick();

        if (Game::GetInstance()->exitMenu())
        {
            std::cout << "test\n";
        }
	}

	Game::GetInstance()->clean();

	return 0;
}