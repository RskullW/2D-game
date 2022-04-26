#include "ProgressBar.h"
#include "Game.h"
#include "Camera.h"

ProgressBar::ProgressBar(std::string textureID):m_pTextureID(textureID){
    m_Animation = new SpriteAnim();
}

void ProgressBar::Draw() {
    m_Animation->Draw(SCREEN_WIDTH+Camera::GetInstance()->GetPosition().X-156, 0, 156, 226);
}

void ProgressBar::Update(float dt) {
    m_aliveVas = Game::GetInstance()->getAliveVas();
    m_aliveStep = Game::GetInstance()->getAliveStep();
    m_alivePal = Game::GetInstance()->getAliveUnk();

    if (m_aliveVas && m_aliveStep && m_alivePal){
        m_Animation->setProps(m_pTextureID, 0, 1, 1000);
    }

    else if (!m_aliveVas && m_aliveStep && m_alivePal){
        m_Animation->setProps(m_pTextureID, 1, 1, 1000);
    }

    else if (m_aliveVas && !m_aliveStep && m_alivePal){
        m_Animation->setProps(m_pTextureID, 2, 1, 1000);
    }

    else if (m_aliveVas && m_aliveStep && !m_alivePal){
        m_Animation->setProps(m_pTextureID, 3, 1, 1000);
    }

    else if (!m_aliveVas && !m_aliveStep && m_alivePal){
        m_Animation->setProps(m_pTextureID, 4, 1, 1000);
    }

    else if (!m_aliveVas && m_aliveStep && !m_alivePal){
        m_Animation->setProps(m_pTextureID, 5, 1, 1000);
    }

    else if (m_aliveVas && !m_aliveStep && !m_alivePal){
        m_Animation->setProps(m_pTextureID, 6, 1, 1000);
    }

    else {
        m_Animation->setProps(m_pTextureID, 7, 1, 1000);
    }

    m_Animation->Update(dt);
}

void ProgressBar::Clean() {
    delete m_Animation;
}