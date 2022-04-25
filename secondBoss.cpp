#include <iostream>
#include <cmath>
#include "secondBoss.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include "ObjectFactory.h"
#include "soundGame.h"

static Registrar<secondBoss> registrar("SECONDBOSS");

static float RUN_FORCE = 1.5;
static float ATTACK_TIME_FIRST = 25.0f;

secondBoss::secondBoss(Properties* props) : Character(props)
{
    isFailing = m_Attacking = false;

    thisRunning = RUN_FORCE;

    m_Collider = new Collider();
    m_Collider->SetBuff(-30, 42, 75, 0);

    m_RigidBody = new RigdBody;
    m_RigidBody->setGravity(3.0f);

    m_Animation = new SpriteAnim();
    m_Animation->setProps(m_pTextureID, 0, 4, 120);

    m_Health = 200;
    m_Damage = 10;
}

void secondBoss::Draw()
{
    if (m_Running || m_Attacking) {
        m_Animation->Draw(m_pTransform->X, m_pTransform->Y, m_W, m_H, 1, 1, m_sFlip);
    }

    Vector2D cam = Camera::GetInstance()->GetPosition();
//	SDL_Rect box = m_Collider->Get();
//	box.x -= cam.X;
//	box.y -= cam.Y;
//	SDL_RenderDrawRect(Game::GetInstance()->GetRenderer(), &box);

    // HP BAR

    if (m_Running || m_Attacking) {
        SDL_Rect hpBar;
        hpBar.x = m_pTransform->X - Camera::GetInstance()->GetPosition().X + 100 / 4;
        hpBar.y = m_pTransform->Y - Camera::GetInstance()->GetPosition().Y - 20;
        hpBar.w = 100 / 2;
        hpBar.h = 15;
        SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), 0, 0, 0, 125);
        SDL_RenderFillRect(Game::GetInstance()->GetRenderer(), &hpBar);
        // Зеленая полоска хпбара
        hpBar.x += 5;
        hpBar.y += 5;
        hpBar.w -= 10;
        hpBar.h -= 10;
        hpBar.w = (double) m_Health / 200 * hpBar.w;
        SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), 0, 255, 0, 255);
        SDL_RenderFillRect(Game::GetInstance()->GetRenderer(), &hpBar);
    }
}

void secondBoss::Update(float dt)
{
    m_Running = 0;
    m_RigidBody->UnSetForce();
    // Stepanov run left
    if ( (m_pTransform->X>=3103) &&(m_pTransform->X - Game::GetInstance()->getPlayer()->GetOrigin()->X)>=-20 && fabs(Game::GetInstance()->getPlayer()->GetOrigin()->X-m_pTransform->X)<=300 && (Game::GetInstance()->getPlayer()->GetOrigin()->X-50 < m_lastSafePos.X)) {
        m_RigidBody->ApplyForceX(-3*thisRunning);
        m_sFlip = SDL_FLIP_HORIZONTAL;
        m_Running = 1;
        nearPlayer = false;

        if (startPhrase == 0)
        {
            startPhrase = 1;
            soundGame::GetInstance()->playEffect("startPhraseStepanov", 4);
            soundGame::GetInstance()->playMusic("startMusicStepanov");
        }
    }

    else if (fabs(Game::GetInstance()->getPlayer()->GetOrigin()->X-m_pTransform->X)<=50)
    {
        nearPlayer = true;
    }

    // Stepanov run right
    if ((m_pTransform->X <=4330) && (Game::GetInstance()->getPlayer()->GetOrigin()->X-m_pTransform->X)>20 && fabs(Game::GetInstance()->getPlayer()->GetOrigin()->X-m_pTransform->X)<=300 && (Game::GetInstance()->getPlayer()->GetOrigin()->X-50 > m_lastSafePos.X)) {
        m_RigidBody->ApplyForceX(3*thisRunning);
        m_sFlip = SDL_FLIP_NONE;
        m_Running = 1;
        nearPlayer = false;

        if (startPhrase == 0)
        {
            startPhrase = 1;
            soundGame::GetInstance()->playEffect("startPhraseStepanov", 4);
            soundGame::GetInstance()->playMusic("startMusicStepanov");

        }
    }

    else if (fabs(Game::GetInstance()->getPlayer()->GetOrigin()->X-m_pTransform->X)<=50)
    {
        nearPlayer = true;
    }

    // Stepanov attacking
    if (m_Attacking == false && nearPlayer)
    {
        m_RigidBody->UnSetForce();
        m_Attacking = 1;
        Game::GetInstance()->getPlayer()->GetHealth()-=m_Damage;
        soundGame::GetInstance()->playEffect("attackStepanov", 3);
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

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        SDL_Log("ERROR");
        m_pTransform->X = m_lastSafePos.X;
    }


    if (CollisionHandler::GetInstance()->MapCollisionDamage(m_Collider->Get()))
    {
        m_pTransform->X = m_lastSafePos.X;
        m_Health-=200;
    };

    m_Collider->Set(m_pTransform->X, m_pTransform->Y, 96, 96);
    m_Origin->X = (m_pTransform->X + m_W / 2);

    if (Game::GetInstance()->getPlayer()->GetHealth()<=0)
    {
        m_Health = 200;
    }

    AnimationState();
    m_Animation->Update(dt);

}

void secondBoss::AnimationState() {
    m_Animation->setProps(m_pTextureID, 0, 4, 120);

    if (m_Running)
    {
        m_Animation->setProps(m_pTextureID, 1, 6, 150);
    }

    if (isFailing) {
        m_Animation->setProps(m_pTextureID, 6, 2, 150);
    }

    if (m_Attacking) {
        m_Animation->setProps(m_pTextureID, 5, 7, 60);
    }


}

void secondBoss::Clean()
{
    TextureManager::GetInstance()->Drop(m_pTextureID);
}