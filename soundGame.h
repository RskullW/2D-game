#pragma once
#include <map>

#include <string>
#include <iostream>
#include "SDL2/SDL_mixer.h"

#define FREQ 44100
#define CHUNK_SIZE 2048


using MusikMap = std::map<std::string, Mix_Music*>;
using EffectMap = std::map<std::string, Mix_Chunk*>;

class soundGame {
public:
    void clean();

    void playMusic(std::string id);
    void loadMusic(std::string id, std::string source);

    void playEffect(std::string id);
    void loadEffect(std::string id, std::string source);

    inline static soundGame* GetInstance() {return s_Instance = (s_Instance != nullptr)?s_Instance:new soundGame();}

private:
    soundGame();
    MusikMap m_musicMap;
    EffectMap m_effectMap;

    static soundGame* s_Instance;
};