#include <iostream>
#include <cmath>
#include "Enemy.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include "ObjectFactory.h"
#include "soundGame.h"

static Registrar<Enemy> registrar("FIRSTBOSS");

static float RUN_FORCE = 0.25f;
static float ATTACK_TIME_FIRST = 30.0f;

Enemy::Enemy(Properties* props) : Character(props)
{
    isFailing = m_Attacking = false;
    thisRunning = RUN_FORCE;

	m_Collider = new Collider();
	m_Collider->SetBuff(-30, -10, 75, 45);

    m_RigidBody = new RigdBody;
    m_RigidBody->setGravity(3.0f);

	m_Animation = new SpriteAnim();
	m_Animation->setProps(m_pTextureID, 0, 10, 150);

    m_Health = 200;
    m_Damage = 25;
}

void Enemy::Draw()
{
	m_Animation->Draw(m_pTransform->X, m_pTransform->Y, m_W, m_H, 1, 1, m_sFlip);

	Vector2D cam = Camera::GetInstance()->GetPosition();
//	SDL_Rect box = m_Collider->Get();
//	box.x -= cam.X;
//	box.y -= cam.Y;
//	SDL_RenderDrawRect(Game::GetInstance()->GetRenderer(), &box);

    // HP BAR
    SDL_Rect hpBar;
    hpBar.x = m_pTransform->X - Camera::GetInstance()->GetPosition().X + 78 / 4;
    hpBar.y = m_pTransform->Y - Camera::GetInstance()->GetPosition().Y - 20;
    hpBar.w = 78 / 2;
    hpBar.h = 15;
    SDL_SetRenderDrawColor( Game::GetInstance()->GetRenderer(), 0, 0, 0, 125 );
    SDL_RenderFillRect( Game::GetInstance()->GetRenderer(), &hpBar );
    // Зеленая полоска хпбара
    hpBar.x += 5;
    hpBar.y += 5;
    hpBar.w -= 10;
    hpBar.h -= 10;
    hpBar.w = (double) m_Health / 200 * hpBar.w;
    SDL_SetRenderDrawColor( Game::GetInstance()->GetRenderer(), 0, 255, 0, 255 );
    SDL_RenderFillRect( Game::GetInstance()->GetRenderer(), &hpBar );
}

void Enemy::Update(float dt)
{
    m_Running = 0;
    m_RigidBody->UnSetForce();
    // Vasukov run left
    if ((m_pTransform->X - Game::GetInstance()->getPlayer()->GetOrigin()->X)>=-20 && fabs(Game::GetInstance()->getPlayer()->GetOrigin()->X-m_pTransform->X)<=400 && (Game::GetInstance()->getPlayer()->GetOrigin()->X-50 < m_lastSafePos.X)) {
        m_RigidBody->ApplyForceX(-3*thisRunning);
        m_sFlip = SDL_FLIP_HORIZONTAL;
        m_Running = 1;
        nearPlayer = false;

        if (startPhrase == 0)
        {
            startPhrase = 1;
            soundGame::GetInstance()->playEffect("startPhraseVasukov", 4);
            soundGame::GetInstance()->playMusic("startMusicVasukov");
        }
    }

    else if (fabs(Game::GetInstance()->getPlayer()->GetOrigin()->X-m_pTransform->X)<=50)
    {
        nearPlayer = true;
    }

    // Vasukov run right
    if ((Game::GetInstance()->getPlayer()->GetOrigin()->X-m_pTransform->X)>20 && fabs(Game::GetInstance()->getPlayer()->GetOrigin()->X-m_pTransform->X)<=400 && (Game::GetInstance()->getPlayer()->GetOrigin()->X-50 > m_lastSafePos.X)) {
        m_RigidBody->ApplyForceX(3*thisRunning);
        m_sFlip = SDL_FLIP_NONE;
        m_Running = 1;
        nearPlayer = false;

        if (startPhrase == 0)
        {
            startPhrase = 1;
            soundGame::GetInstance()->playEffect("startPhraseVasukov");
            soundGame::GetInstance()->playMusic("startMusicVasukov");

        }
    }

    else if (fabs(Game::GetInstance()->getPlayer()->GetOrigin()->X-m_pTransform->X)<=50)
    {
        nearPlayer = true;
    }

    // Vasukov attacking
    if (m_Attacking == false && nearPlayer)
    {
        m_RigidBody->UnSetForce();
        m_Attacking = 1;
        Game::GetInstance()->getPlayer()->GetHealth()-=m_Damage;
        soundGame::GetInstance()->playEffect("attackVas", 3);
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

void Enemy::AnimationState() {
    m_Animation->setProps(m_pTextureID, 0, 10, 150);

    if (m_Running)
    {
        m_Animation->setProps(m_pTextureID, 2, 10, 150);
    }

    if (isFailing) {
        m_Animation->setProps(m_pTextureID, 4, 10, 150);
    }

    if (m_Attacking) {
        m_Animation->setProps(m_pTextureID, 3, 10, 150);
    }


}

void Enemy::Clean()
{
    TextureManager::GetInstance()->Drop(m_pTextureID);
}