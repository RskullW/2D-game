#include "Warrior.h"
#include "TextureManager.h"
#include <SDL2/SDL.h>
#include <cmath>
#include "input.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include "Game.h"
#include "ObjectFactory.h"
#include "soundGame.h"

static int tempTime = 0;

static float RUN_FORCE = 0.25f;
static float JUMP_TIME = 8.0f;
static float JUMP_FORCE = 6.0f;

static Registrar<Warrior> registrar("PLAYER");


Warrior::Warrior(Properties* props): Character(props)
{
    isFailing = 0;
	hackSpeed.cntButton = hackJump.cntButton = 0;
	hackSpeed.cheatActivated = hackJump.cheatActivated = 0;

	m_JumpTime = JUMP_TIME;
	m_JumpForce = JUMP_FORCE; 
	thisRunning = RUN_FORCE;

	m_Collider = new Collider();
	m_Collider->SetBuff(-45, -50, 75, 50);

	m_RigidBody = new RigdBody();
	m_RigidBody->setGravity(3.0f);

	m_Animation = new SpriteAnim();
	m_Animation->setProps(m_pTextureID, 0, 6, 120);

    m_Health = 200;
    m_Damage = 40;

    // Location HPbar
    m_AnimationHP = new SpriteAnim();
    m_AnimationHP->setProps("hp", 0, 5, 150);
}

void Warrior::Draw()
{
	m_Animation->Draw(m_pTransform->X, m_pTransform->Y, m_W, m_H, 1, 1, m_sFlip);
    m_AnimationHP->Draw(cam.X, 0, 289, 45);

    cam = Camera::GetInstance()->GetPosition();

//	SDL_Rect box = m_Collider->Get();
//	box.x -= cam.X;
//	box.y -= cam.Y;
//	SDL_RenderDrawRect(Game::GetInstance()->GetRenderer(), &box);
}

void Warrior::DrawDeath(std::string nameSound) {

    if (isFailing == 1) {
        tempTime++;
        SDL_Rect tempsrc = {0, 0, 960, 640}, tempdest = {0, 0, 960, 640};

        soundGame::GetInstance()->stopMusic();

        if (tempTime == 50) {

            soundGame::GetInstance()->playEffect(nameSound, 2);
            m_Health = 200;
            m_LastSafePos.X = m_pTransform->X = m_Origin->X = 40;
            m_LastSafePos.Y = m_pTransform->Y = m_Origin->X = 460;

            while (isFailing) {
                SDL_RenderClear(Game::GetInstance()->GetRenderer());
                SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), 0, 0, 0, 0);

                SDL_RenderCopy(Game::GetInstance()->GetRenderer(), TextureManager::GetInstance()->getTexture("death"),
                               &tempsrc, &tempdest);

                SDL_RenderPresent(Game::GetInstance()->GetRenderer());

                SDL_Event ev;
                if (SDL_PollEvent(&ev)) {
                    tempTime = 0;
                    isFailing = 0;
                    Game::GetInstance()->getFirstBoss()->GetStartPhrase() = 0;
                }
            }
        }
    }
}


void Warrior::Clean()
{
	TextureManager::GetInstance()->Drop(m_pTextureID);
}

void Warrior::Update(float dt)
{
	m_RigidBody->UnSetForce();

	if (input::GetInstance()->GetAxisRey(HORIZONTAL) == FORWARD && !m_Attacking)
	{
        if (m_Running == 0 || m_Jumping)
        {
            soundGame::GetInstance()->playEffect("sound_run", 1);
        }

		if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_LSHIFT))
		{
			thisRunning = 0.4f;
		}

		else
		{
			thisRunning = RUN_FORCE;
		}
		m_RigidBody->ApplyForceX(3* thisRunning);
		m_sFlip = SDL_FLIP_NONE;
		m_Running = 1;
	}

	if (input::GetInstance()->GetAxisRey(HORIZONTAL) == BACKWARD && !m_Attacking)
	{
        if (m_Running == 0 || m_Jumping)
        {
            soundGame::GetInstance()->playEffect("sound_run", 1);
        }
        if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_LSHIFT))
		{
            SDL_Log("HERO: axisX = %.0f || axisY = %.0f", m_pTransform->X, m_pTransform->Y);
            thisRunning = 0.4f;
		}

		else
		{
			thisRunning = RUN_FORCE;
		}

		m_RigidBody->ApplyForceX(3* thisRunning*-1);
		m_sFlip = SDL_FLIP_HORIZONTAL;
		m_Running = 1;
	
	}

	// Stoping
	if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
	{
		m_RigidBody->UnSetForce();
    }

	// Attacking
	if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_LCTRL) && m_Grounded)
	{
        if (m_Attacking == 0)
        {
            soundGame::GetInstance()->playEffect("attack", 2);

            if (Game::GetInstance()->getFirstBoss()->GetNearPlayer())
            {
                Game::GetInstance()->getFirstBoss()->GetHealth()-=m_Damage;
            }

            if (Game::GetInstance()->getSecondBoss()->GetNearPlayer())
            {
                Game::GetInstance()->getSecondBoss()->GetHealth()-=m_Damage;
            }
        }
		m_RigidBody->UnSetForce();
		m_Attacking = 1;
	}

	// Jump
	if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_Grounded)
	{
        if (m_Jumping == 0)
        {
            soundGame::GetInstance()->stopEffect(1);
        }

		m_Jumping = 1;
		m_Grounded = 0;
		m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
        soundGame::GetInstance()->playEffect("sound_jump", 2);
	}
    // Hold jump
	if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_Jumping && m_JumpTime > 0)
	{

		m_JumpTime -= dt;
		m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
		m_AccelarationFactorJump += 0.01;

	}

	else
	{
		m_Jumping = 0;
		m_JumpTime = JUMP_TIME;
	}
    // Click pause
    if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)){
        userButEscape = true;
        soundGame::GetInstance()->playEffect("open_menu", -1);
    }

	// Death collision map
    if (CollisionHandler::GetInstance()->MapCollisionDamage(m_Collider->Get()) ) {
        m_pTransform->X = m_LastSafePos.X;
        isFailing = 1;
        DrawDeath("sound_die");
        soundGame::GetInstance()->playMusic("startMenu");
    }

    else if (m_Health<=0){
        isFailing = 1;
        DrawDeath("sound_die_enemy");
        soundGame::GetInstance()->playMusic("startMenu");
    }

	else {
        isFailing = 0;
    }

	// Attack time
	if (m_Attacking && m_AttackTime > 0)
	{
		m_AttackTime -= dt;
	}

	else
	{
		m_Attacking = 0;
		m_AttackTime = ATTACK_TIME;
	}

    CheatSpeed();
	CheatJump();

    if (m_LastSafePos.X == m_pTransform->X && m_Jumping == false && m_Attacking == false){
        soundGame::GetInstance()->stopEffect(1);
        m_Running = 0;
    }

    // Collision Vasukov
    if ( fabs(Game::GetInstance()->getFirstBoss()->getPosEnemy().X-m_pTransform->X)<=30 && fabs(Game::GetInstance()->getFirstBoss()->getPosEnemy().Y-m_pTransform->Y)<=52 && Game::GetInstance()->getFirstBoss()->GetHealth()>0) {
        if (m_Jumping) {
            m_pTransform->Y-=5;

            if (input::GetInstance()->GetAxisRey(HORIZONTAL)==FORWARD) {
                m_pTransform->X = m_LastSafePos.X+25;
            }

            else
            {
                m_pTransform->X = m_LastSafePos.X - 25;
            }
        }

        else {
            m_pTransform->X = m_LastSafePos.X;
        }
    }

	// axis X
	m_RigidBody->Update(dt);
	m_LastSafePos.X = m_pTransform->X;
	m_pTransform->X += m_RigidBody->getPosition().X;
	m_Collider->Set(m_pTransform->X, m_pTransform->Y, 96, 96);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
	{
		m_pTransform->X = m_LastSafePos.X;
	}

    if (CollisionHandler::GetInstance()->MapCollisionDamage(m_Collider->Get()))
    {
        m_pTransform->X = m_LastSafePos.X;
        m_Health = -1;
    }

	// axis Y 
	m_RigidBody->Update(dt);
	m_LastSafePos.Y = m_pTransform->Y;
	if (!m_Grounded && !m_Jumping)
	{
		if (!m_JumpDown)
		{
			m_JumpDown = 1;
			m_AccelarationFactorJump /= 2;
		}
			m_pTransform->Y += m_RigidBody->getPosition().Y*(m_AccelarationFactorJump+=0.1f);
	}
	
	else
	{
		m_pTransform->Y += m_RigidBody->getPosition().Y;
	}

	m_Collider->Set(m_pTransform->X, m_pTransform->Y, 96, 96);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) 
	{
		m_JumpDown = 0;
		m_AccelarationFactorJump = 0.1f;
		m_Grounded = 1;
		m_pTransform->Y = m_LastSafePos.Y;
	}

	else
	{
		m_Grounded = 0;
	}

	m_Origin->X = (m_pTransform->X + m_W / 2);
	m_Origin->Y = (m_pTransform->Y + m_H / 2);

    if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_9))
    {
        m_pTransform->X = m_LastSafePos.X = 50;
        m_pTransform->Y = m_LastSafePos.Y = 460;
    }

	AnimationState();
	m_Animation->Update(dt);
    AnimationHPBAR();
    m_AnimationHP->Update(dt);
}
void Warrior::AnimationState()
{

    m_Animation->setProps("player", 0, 6, 120);

    if (isFailing)
    {
        m_Animation->setProps("player", 5, 8, 380);
    }

    if (m_Attacking)
    {
        m_Animation->setProps("player", 1, 6, 80);
    }

    if (m_Running)
    {
        m_Animation->setProps("player", 2, 8, 120);
    }

    if (m_Jumping)
    {
        m_Animation->setProps("player", 3, 8, 150);
    }

}

void Warrior::AnimationHPBAR()
{

    if (m_Health==200)
    {
        m_AnimationHP->setProps("hp", 0, 5, 150);
    }

    else if (m_Health==175)
    {
        m_AnimationHP->setProps("hp", 1, 5, 150);
    }

    else if (m_Health==150)
    {
        m_AnimationHP->setProps("hp", 2, 5, 150);
    }

    else if (m_Health==125)
    {
        m_AnimationHP->setProps("hp", 3, 5, 150);
    }

    else if (m_Health==100)
    {
        m_AnimationHP->setProps("hp", 4, 5, 150);
    }

    else if (m_Health==75)
    {
        m_AnimationHP->setProps("hp", 5, 5, 150);
    }

    else if (m_Health==50)
    {
        m_AnimationHP->setProps("hp", 6, 5, 150);
    }

    else if (m_Health==25)
    {
        m_AnimationHP->setProps("hp", 7, 5, 150);
    }
}

void Warrior::CheatSpeed()
{
	if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && (hackSpeed.cntButton == 0 || hackSpeed.cntButton == 1))
	{
		SDL_Log("enter button 'A'\n");
		hackSpeed.cntButton = 1;
		hackSpeed.numCheats[0] = 1;
	}

	else if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_E) && (hackSpeed.cntButton == 1 || hackSpeed.cntButton == 2))
	{
		SDL_Log("enter button 'E'\n");
		hackSpeed.cntButton = 2;
		hackSpeed.numCheats[1] = 1;
	}

	else if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_Z) && (hackSpeed.cntButton == 2 || hackSpeed.cntButton == 3))
	{
		SDL_Log("enter button 'Z'\n");
		hackSpeed.cntButton = 3;
		hackSpeed.numCheats[2] = 1;
	}

	else if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && (hackSpeed.cntButton == 3 || hackSpeed.cntButton == 4))
	{
		SDL_Log("enter button 'A'\n");
		hackSpeed.cntButton = 4;
		hackSpeed.numCheats[3] = 1;
	}

	else if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_K) && (hackSpeed.cntButton == 4 || hackSpeed.cntButton == 5))
	{
		SDL_Log("enter button 'K'\n");
		hackSpeed.cntButton = 5;
		hackSpeed.numCheats[4] = 1;
	}

	else if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_M) && (hackSpeed.cntButton == 5 || hackSpeed.cntButton == 6))
	{
		SDL_Log("enter button 'M'\n");
		hackSpeed.cntButton = 6;
		hackSpeed.numCheats[5] = 1;
	}

	else if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_I) && (hackSpeed.cntButton == 6 || hackSpeed.cntButton == 7))
	{
		hackSpeed.cntButton = 7;
		hackSpeed.numCheats[6] = 1;
		SDL_Log("enter button 'I'\n");
	}

	else if (input::GetInstance()->GetKey() != 0)
	{

		SDL_Log("Reset activated cheats");
		clearInputCheats(hackSpeed.numCheats, 7);
		hackSpeed.cntButton = 0;
	}

	if (hackSpeed.cntButton == 7)
	{
		if (!hackSpeed.cheatActivated)
		{
			SDL_Log("CHEAT SPEED ACTIVATED\n");
			RUN_FORCE = 1.f;
			hackSpeed.cheatActivated = 1;
            m_Health = 1500;
		}

		else
		{
			SDL_Log("CHEAT SPEED DEACTIVATED\n");
			RUN_FORCE = 0.25f;
			hackSpeed.cheatActivated = 0;
            m_Health = 200;
		}

		hackSpeed.cntButton = 0;
	}
}

void Warrior::CheatJump()
{
	if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_H) && (hackJump.cntButton == 0 || hackJump.cntButton == 1))
	{
		SDL_Log("enter button 'H'\n");
		hackJump.cntButton = 1;
		hackJump.numCheats[0] = 1;
	}

	else if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_E) && (hackJump.cntButton == 1 || hackJump.cntButton == 2))
	{
		SDL_Log("enter button 'E'\n");
		hackJump.cntButton = 2;
		hackJump.numCheats[1] = 1;
	}

	else if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_S) && (hackJump.cntButton == 2 || hackJump.cntButton == 3))
	{
		SDL_Log("enter button 'S'\n");
		hackJump.cntButton = 3;
		hackJump.numCheats[2] = 1;
	}

	else if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_O) && (hackJump.cntButton == 3 || hackJump.cntButton == 4))
	{
		SDL_Log("enter button 'O'\n");
		hackJump.cntButton = 4;
		hackJump.numCheats[3] = 1;
	}

	else if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_Y) && (hackJump.cntButton == 4 || hackJump.cntButton == 5))
	{
		SDL_Log("enter button 'Y'\n");
		hackJump.cntButton = 5;
		hackJump.numCheats[4] = 1;
	}

	else if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && (hackJump.cntButton == 5 || hackJump.cntButton == 6))
	{
		SDL_Log("enter button 'A'\n");
		hackJump.cntButton = 6;
		hackJump.numCheats[5] = 1;
	}

	else if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_M) && (hackJump.cntButton == 6 || hackJump.cntButton == 7))
	{
		SDL_Log("enter button 'M'\n");
		hackJump.cntButton = 7;
		hackJump.numCheats[6] = 1;
	}

	else if (input::GetInstance()->GetKey() != 0)
	{

		SDL_Log("Reset activated cheats");
		clearInputCheats(hackJump.numCheats, 7);
		hackJump.cntButton = 0;
	}

	if (hackJump.cntButton == 7)
	{
		if (!hackJump.cheatActivated)
		{
			SDL_Log("CHEAT JUMP ACTIVATED\n");
			JUMP_TIME = 15.0f;
			JUMP_FORCE = 10.0f;
			hackJump.cheatActivated = 1;
		}

		else
		{
			SDL_Log("CHEAT JUMP DEACTIVATED\n");
			JUMP_TIME = 8.0f;
			JUMP_FORCE = 6.0f;
			hackJump.cheatActivated = 0;
		}

		hackJump.cntButton = 0;
	}
}

void Warrior::clearInputCheats(bool* clickButton, int num)
{
	for (int i = 0; i < num; ++i)
		clickButton[i] = 0;
}