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
    void stopMusic();

    void playEffect(std::string id, int channel = -1, int loops = 0);
    void loadEffect(std::string id, std::string source, int channel = -1);
    void stopEffect(int channel = -1);

    void freeChunk(std::string id);

    inline static soundGame* GetInstance() {return s_Instance = (s_Instance != nullptr)?s_Instance:new soundGame();}

private:
    soundGame();
    MusikMap m_musicMap;
    EffectMap m_effectMap;

    static soundGame* s_Instance;
};