#include "FontsManager.h"
#include <iostream>

FontsManager* FontsManager::s_Instance = nullptr;

void FontsManager::Add(std::string path, std::string id, int size) {

    if (TTF_Init()!=0)
    {
        std::cout << TTF_GetError() << '\n';
        return;
    }

    TTF_Font* p_Font = TTF_OpenFont(path.c_str(), size);

    if (p_Font == NULL)
    {
        std::cout << TTF_GetError() << " Path: " << path << '\n';
        return;
    }

    m_FontMap[id] = p_Font;
}

void FontsManager::clearID(std::string id) {
    m_FontMap.erase(id);
}

void FontsManager::clear(){
    m_FontMap.clear();
}

TTF_Font* FontsManager::GetFont(std::string id)
{
    if (m_FontMap[id] == nullptr)
    {
        throw -1;
    }

    return m_FontMap[id];
}
