#pragma once
#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class FontsManager {
public:
    static FontsManager* GetInstance() {return s_Instance = (s_Instance !=nullptr)? s_Instance: new FontsManager();}

    void Add(std::string path, std::string id, int size);
    void clearID(std::string id);
    void clear();

    TTF_Font* GetFont(std::string id);

private:
    FontsManager() {};

private:

    std::map<std::string, TTF_Font*> m_FontMap;
    static FontsManager* s_Instance;

};