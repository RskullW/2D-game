#include "input.h"
#include "Game.h"

input* input::s_Instance = nullptr;


input::input()
{
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void input::Listen()
{
	SDL_Event mEvent;

	while (SDL_PollEvent(&mEvent))
	{
		switch (mEvent.type)
		{
		case SDL_QUIT: Game::GetInstance()->set_mbRunning(0); break;
		case SDL_KEYDOWN: KeyDown(); break;
		case SDL_KEYUP: KeyUp(); break;
		default:break;
		}
	}
}

bool input::GetKeyDown(SDL_Scancode key)
{
	return (m_KeyStates[key] == 1);
}

void input::KeyUp()
{
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void input::KeyDown()
{
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

int input::GetAxisRey(Axis axis)
{
	switch (axis)
	{
	case HORIZONTAL:
	{
		if (GetKeyDown(SDL_SCANCODE_D) || GetKeyDown(SDL_SCANCODE_RIGHT))
		{
			return -1;
		}

		if (GetKeyDown(SDL_SCANCODE_A) || GetKeyDown(SDL_SCANCODE_LEFT))
		{
			return 1;
		}
	}break;

	case VERTICAL:
	{
		if (GetKeyDown(SDL_SCANCODE_W) || GetKeyDown(SDL_SCANCODE_UP) || GetKeyDown(SDL_SCANCODE_SPACE))
		{
			return 1;
		}
		if (GetKeyDown(SDL_SCANCODE_S) || GetKeyDown(SDL_SCANCODE_DOWN))
		{
			return -1;
		}
	}break;

	default: return 0;
	}
}

bool input::GetKey()
{
	SDL_Event tEvent;
	SDL_PollEvent(&tEvent);
	return ((tEvent.type == SDL_KEYUP) ? 1 : 0);
}

bool input::GetMouseButton() {
    SDL_Event ev;
    SDL_PollEvent(&ev);
    return ((ev.type == SDL_MOUSEBUTTONDOWN)?1:0);
}