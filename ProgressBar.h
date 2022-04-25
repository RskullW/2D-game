#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "SpriteAnim.h"
#include "string"

class ProgressBar {
public:
    ProgressBar(std::string textureID);

    void Update(float dt);
    void Draw();
    void Clean();

private:
    bool m_alivePal, m_aliveStep, m_aliveVas;
    std::string m_pTextureID;
    SpriteAnim* m_Animation;
};