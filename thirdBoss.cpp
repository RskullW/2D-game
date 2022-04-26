#include <iostream>
#include <cmath>
#include "thirdBoss.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include "ObjectFactory.h"
#include "soundGame.h"

static Registrar<ThirdBoss> registrar("THIRDBOSS");

static float RUN_FORCE = 0.5f;
static float ATTACK_TIME_FIRST = 200.0f;

ThirdBoss::ThirdBoss(Properties* props) : Character(props)
{
    isFailing = m_Attacking = false;

    thisRunning = RUN_FORCE;

    m_Collider = new Collider();
    m_Collider->SetBuff(-10, 40, 30, 20);

    m_RigidBody = new RigdBody;
    m_RigidBody->setGravity(3.0f);

    m_Animation = new SpriteAnim();
    m_Animation->setProps(m_pTextureID, 0, 4, 120);

    m_Health = 400;
    m_Damage = 25;

    m_Bullet = new Bullet("ammo", 0, 0, 81, 53);
}

void ThirdBoss::Draw()
{
    m_Animation->Draw(m_pTransform->X, m_pTransform->Y, m_W, m_H, 1, 1, m_sFlip);

    Vector2D cam = Camera::GetInstance()->GetPosition();
//	SDL_Rect box = m_Collider->Get();
//	box.x -= cam.X;
//	box.y -= cam.Y;
//	SDL_RenderDrawRect(Game::GetInstance()->GetRenderer(), &box);

    // HP BAR
        SDL_Rect hpBar;
        hpBar.x = m_pTransform->X - Camera::GetInstance()->GetPosition().X + 80 / 4;
        hpBar.y = m_pTransform->Y - Camera::GetInstance()->GetPosition().Y - 20;
        hpBar.w = 80 / 2;
        hpBar.h = 15;
        SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), 0, 0, 0, 125);
        SDL_RenderFillRect(Game::GetInstance()->GetRenderer(), &hpBar);
        // Зеленая полоска хпбара
        hpBar.x += 5;
        hpBar.y += 5;
        hpBar.w -= 10;
        hpBar.h -= 10;
        hpBar.w = (double) m_Health / 400 * hpBar.w;
        SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), 0, 255, 0, 255);
        SDL_RenderFillRect(Game::GetInstance()->GetRenderer(), &hpBar);

    if (m_Bullet->GetAddBullet())
    {
        m_Bullet->Draw();
    }

}

void ThirdBoss::Update(float dt)
{
    m_Running = 0;
    m_RigidBody->UnSetForce();
    // Unknown person run left
    if ((m_pTransform->X - Game::GetInstance()->getPlayer()->GetOrigin()->X)>=300 && fabs(Game::GetInstance()->getPlayer()->GetOrigin()->X-m_pTransform->X)<=600 && (Game::GetInstance()->getPlayer()->GetOrigin()->X-50 < m_lastSafePos.X)) {
        m_RigidBody->ApplyForceX(-3*thisRunning);
        m_sFlip = SDL_FLIP_HORIZONTAL;
        m_Running = 1;
        nearPlayer = true;

        if (startPhrase == 0)
        {
            startPhrase = 1;
            soundGame::GetInstance()->playEffect("startPhraseUnk", 4);
            soundGame::GetInstance()->playMusic("startMusicUnk");
        }
    }

    else if (fabs(Game::GetInstance()->getPlayer()->GetOrigin()->X-m_pTransform->X)<=300)
    {
        if (Game::GetInstance()->getPlayer()->GetOrigin()->X<m_pTransform->X) {
            m_sFlip = SDL_FLIP_HORIZONTAL;
        }

        nearPlayer = true;
    }

    else {
        nearPlayer = false;
    }

    // Unknown person run right
    if ((Game::GetInstance()->getPlayer()->GetOrigin()->X-m_pTransform->X)>=300 && fabs(Game::GetInstance()->getPlayer()->GetOrigin()->X-m_pTransform->X)<=600 && (Game::GetInstance()->getPlayer()->GetOrigin()->X-50 > m_lastSafePos.X)) {
        m_RigidBody->ApplyForceX(3*thisRunning);
        m_sFlip = SDL_FLIP_NONE;
        m_Running = 1;
        nearPlayer = true;

        if (startPhrase == 0)
        {
            startPhrase = 1;
            soundGame::GetInstance()->playEffect("startPhraseUnk", 4);
            soundGame::GetInstance()->playMusic("startMusicUnk");

        }
    }

    else if (fabs(Game::GetInstance()->getPlayer()->GetOrigin()->X-m_pTransform->X)<=300)
    {
        if (Game::GetInstance()->getPlayer()->GetOrigin()->X>=m_pTransform->X) {
            m_sFlip = SDL_FLIP_NONE;
        }

        nearPlayer = true;
    }

    else {
        nearPlayer = false;
    }

    // Unknown person attacking
    if (m_Attacking == false && nearPlayer)
    {
        if (m_Attacking == 0)
        {
            soundGame::GetInstance()->playEffect("attackUnk", 3);
            m_Bullet->Add(m_pTransform->X, m_pTransform->Y-24, Game::GetInstance()->getPlayer()->GetOrigin()->X, Game::GetInstance()->getPlayer()->GetOrigin()->Y-24);
        }

        m_RigidBody->UnSetForce();
        m_Attacking = 1;
    }

    // Attack time
    if (m_Attacking && m_AttackTime > 0)
    {
        m_AttackTime -= dt;
    }

    else {
        nearPlayer = 0;
        m_Attacking = 0;
        m_AttackTime = ATTACK_TIME_FIRST;
    }

    // axis X
    m_RigidBody->Update(dt);
    m_lastSafePos.X = m_pTransform->X;
    m_pTransform->X += m_RigidBody->getPosition().X;
    m_Collider->Set(m_pTransform->X, m_pTransform->Y, 96, 96);

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
        SDL_Log("ERROR");
        m_pTransform->X = m_lastSafePos.X;
    }


    if (CollisionHandler::GetInstance()->MapCollisionDamage(m_Collider->Get())) {
        m_pTransform->X = m_lastSafePos.X;
        m_Health -= 200;
    }

    m_Collider->Set(m_pTransform->X, m_pTransform->Y, 96, 96);
    m_Origin->X = (m_pTransform->X + m_W / 2);

    if (Game::GetInstance()->getPlayer()->GetHealth()<=0) {
        m_Health = 200;
    }

    if (m_Bullet->GetAddBullet()) {
        Vector2D positionPlayer;
        positionPlayer.X = Game::GetInstance()->getPlayer()->GetOrigin()->X;
        positionPlayer.Y = Game::GetInstance()->getPlayer()->GetOrigin()->Y;

        if (m_Bullet->CheckPosition(positionPlayer) == true) {
            Game::GetInstance()->getPlayer()->GetHealth() -= m_Damage;
        }
    }

    AnimationState();
    m_Animation->Update(dt);
    m_Bullet->Update(dt);

}

void ThirdBoss::AnimationState() {
    m_Animation->setProps(m_pTextureID, 0, 4, 120);

    if (m_Running)
    {
        m_Animation->setProps(m_pTextureID, 5, 4, 150);
    }

    if (isFailing) {
        m_Animation->setProps(m_pTextureID, 4, 10, 150);
    }

    if (m_Attacking) {
        m_Animation->setProps(m_pTextureID, 2, 7, 120);
    }


}

void ThirdBoss::Clean()
{
    TextureManager::GetInstance()->Drop(m_pTextureID);
    delete m_Bullet;
    delete m_Animation;
}