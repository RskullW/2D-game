#pragma once

#include <SDL2/SDL.h>

enum Axis { HORIZONTAL, VERTICAL };

class input
{
public:
	static input* GetInstance()
	{
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new input();
	}

	void Listen();
	bool GetKeyDown(SDL_Scancode key);
	bool GetKey();
    bool GetMouseButton();

	int GetAxisRey(Axis axis);

private:
	input();
	void KeyUp();
	void KeyDown();

	const Uint8* m_KeyStates;

	static input* s_Instance;
};

