#include "Timer.h"
#include "FontsManager.h"
#include "Game.h"
#include "Camera.h"

Timer* Timer::s_Instance = nullptr;

void Timer::Tick()
{
	m_DeltaTime = (SDL_GetTicks() - m_LastTime) * (TARGET_FPS / 1000.0f);

	if (m_DeltaTime > TARGET_DELTATIME)
	{
		m_DeltaTime = TARGET_DELTATIME;
	}

	m_LastTime = SDL_GetTicks(); 
}

void Timer::Start() {
    timeNow = 0;
}

void Timer::Draw(std::string id) {
    timeFloat+= m_DeltaTime;
    std::string timeString = "";
    SDL_Color colorText = {255, 255, 255, 255};
    SDL_Rect src = {310, 5, 0, 0};

    if (int(timeFloat)/60==1){
        timeFloat = 0.0f;
        timeNow+=1;
    }

    if (timeNow<60){
        timeString = "00:";
        if (timeNow<10){
            timeString+="0";
        }
        timeString+=std::to_string(timeNow);
    }

    else{
        if (timeNow/60<10){
            timeString = "0";
        }

        timeString+= std::to_string(timeNow/60) + ":";

        if ((timeNow%60)<10){
            timeString+="0";
        }
        timeString+=std::to_string(timeNow%60);
    }

    try {
        m_pSurfaceTxt = TTF_RenderText_Solid(FontsManager::GetInstance()->GetFont(id), timeString.c_str(), colorText);
        if (m_pSurfaceTxt == nullptr){
            SDL_Log("Error! Font do not exist, surface not loaded...");
        }
        m_pTextureTxt = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), m_pSurfaceTxt);
        if (m_pTextureTxt==nullptr){
            SDL_Log("Error! Font do not exist, texture not loaded...");
        }
        SDL_FreeSurface(m_pSurfaceTxt);

        SDL_QueryTexture(m_pTextureTxt, NULL, NULL, &src.w, &src.h);
        SDL_RenderCopy(Game::GetInstance()->GetRenderer(), m_pTextureTxt, NULL, &src);
    }

    catch(int& txt)
    {
        std::cout << "LOAD FONT: " << txt;
    }
}