#include "Bullet.h"
#include "CollisionHandler.h"
#include "Camera.h"

Bullet::Bullet(std::string id, int x, int y, int w, int h):m_pTextureID(id) {
    m_Size.x = w;
    m_Size.y = h; m_Size.w = w; m_Size.h = h;

    m_AddBullet = false;
    m_AnimationBullet = new SpriteAnim();

    m_AnimationBullet->setProps(m_pTextureID, 0, 8, 120);

    m_pTextureID = id;
}

void Bullet::Add(int startX, int startY, int endX, int endY) {
    m_AddBullet = true;

    m_coordinate.startX = startX+40;
    m_coordinate.startY = startY+20;
    m_coordinate.endX = endX;
    m_coordinate.endY = endY+20;
}

bool Bullet::CheckPosition(Vector2D coordNPC) {

    if (m_AddBullet) {

        SDL_Rect temp;

        temp.x = m_coordinate.startX;
        temp.y = m_coordinate.startY;
        temp.w = m_Size.w;
        temp.h = m_Size.h;
        if (CollisionHandler::GetInstance()->MapCollision(temp))
        {
            m_AddBullet = false;
            return 0;
        }

        if (abs(m_coordinate.startY-m_coordinate.endY)<=5 && abs(m_coordinate.startX-m_coordinate.endX)<=5 )
        {
            m_AddBullet = false;
            return 0;
        }

        if (m_coordinate.startX>m_coordinate.endX) {
            m_coordinate.startX+=1;
            m_Size.x+=1;
        }

        else if (m_coordinate.startX < m_coordinate.endX) {
            m_coordinate.startX-=1;
            m_Size.x-=1;
        }

        else {
            m_AddBullet = false;
        }

        if (m_coordinate.startY>m_coordinate.endY) {
            m_coordinate.startY+=1;
            m_Size.y+=1;
        }

        else if (m_coordinate.startY<m_coordinate.endY)
        {
            m_coordinate.startY-=1;
            m_Size.y-=1;
        }

        else {
            m_coordinate.startY = m_coordinate.startY;
        }
        // 510 - axisY firstBoss
        if (abs(m_coordinate.startX-coordNPC.X)<=30 && abs(m_coordinate.startY - 510)<=30) {
            m_AddBullet = false;
            return 1;
        }

    }

    return 0;

}

void Bullet::Draw()
{
    m_AnimationBullet->Draw(m_coordinate.startX, m_coordinate.startY, m_Size.w, m_Size.h);
}

void Bullet::Update(float dt) {
    m_AnimationBullet->Update(dt);
}