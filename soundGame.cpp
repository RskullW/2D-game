#include "soundGame.h"

soundGame* soundGame::s_Instance = nullptr;

soundGame::soundGame() {
    Mix_AllocateChannels(5);
    if (Mix_OpenAudio(FREQ, MIX_DEFAULT_FORMAT, 4, CHUNK_SIZE) < 0)
    {
        std::cerr << Mix_GetError() << "\n";
    }
}

void soundGame::playMusic(std::string id) {
    if (Mix_PlayMusic(m_musicMap[id], -1) == -1)
    {
        std::cerr << Mix_GetError() << ": " << id << '\n';
    }
}

void soundGame::stopMusic()
{
    Mix_HaltMusic();
}

void soundGame::loadMusic(std::string id, std::string source) {
    Mix_Music* music = Mix_LoadMUS(source.c_str());

    if (music!= nullptr){
        m_musicMap[id] = music;
    }

    else
    {
        std::cerr << Mix_GetError() << ": " << source << '\n';
    }
}

void soundGame::playEffect(std::string id, int channel, int loops) {
    if (Mix_PlayChannel(channel, m_effectMap[id], loops) == -1){
        std::cerr << Mix_GetError() << ": " << id << '\n';
    }
}

void soundGame::stopEffect(int channel)
{
        Mix_HaltChannel(channel);
}

void soundGame::loadEffect(std::string id, std::string source, int channel) {
    Mix_Chunk* effect = Mix_LoadWAV(source.c_str());
    if (effect != nullptr)
    {
        m_effectMap[id] = effect;
    }

    else
    {
        std::cerr << Mix_GetError() << ": " << source << '\n';
    }
}

void soundGame::clean() {
    for (MusikMap::iterator it = m_musicMap.begin(); it!=m_musicMap.end(); ++it)
    {
        Mix_FreeMusic(it->second);
    }

    for (EffectMap::iterator it = m_effectMap.begin(); it!=m_effectMap.end(); ++it)
    {
        Mix_FreeChunk(it->second);
    }

    m_musicMap.clear();
    m_effectMap.clear();
}