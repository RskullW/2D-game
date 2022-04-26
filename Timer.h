#pragma once
#include <SDL2/SDL.h>
#include <iostream>

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5f;
 
class Timer
{
public:
	inline static Timer* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer();   }
	inline float GetDeltaTime() { return m_DeltaTime; }
	void Tick();

    void Start();
    bool GetStart() {return m_isStart;};
    void Draw(std::string id);


private:
	Timer() {};
	static Timer* s_Instance;

    float  m_resultTime;
    int timeNow = 0;
    float timeFloat = 0;
    bool m_isStart;

	float m_DeltaTime, m_LastTime;
private:
    SDL_Surface* m_pSurfaceTxt;
    SDL_Texture* m_pTextureTxt;
};

