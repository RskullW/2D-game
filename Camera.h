#pragma once

#include <SDL2/SDL.h>
#include "Pointer.h"
#include "Vector2D.h"
#include "Game.h"

class Camera
{
public:
	inline static Camera* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera(); }
	inline SDL_Rect GetViewBox() { return m_ViewBox; }
	inline Vector2D GetPosition() { return m_Position; }
	inline void SetTarget(Pointer* target) { m_Target = target; }
	void Update(float dt);

private:
	Camera() { m_ViewBox = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT }; }
	Pointer* m_Target;
	Vector2D m_Position;
	SDL_Rect m_ViewBox;
	static Camera* s_Instance;
};

