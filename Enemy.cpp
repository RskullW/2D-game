#include "Enemy.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include "ObjectFactory.h"
#include <iostream>


static Registrar<Enemy> registrar("FIRSTBOSS");

Enemy::Enemy(Properties* props) : Character(props)
{ 
	m_RigidBody = new RigdBody;
	m_RigidBody->setGravity(3.0f);
	m_Collider = new Collider();
	m_Collider->SetBuff(-30, -10, 70, 30);
	m_Animation = new SpriteAnim();
	m_Animation->setProps(m_pTextureID, 0, 10, 250); // ID текстуры, номер строки анимации-1, количество столбцов, скорость

}

void Enemy::Draw()
{
	m_Animation->Draw(m_pTransform->X, m_pTransform->Y, m_W, m_H, 1, 1, m_sFlip);

	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect box = m_Collider->Get();
	box.x -= cam.X;
	box.y -= cam.Y;
	SDL_RenderDrawRect(Game::GetInstance()->GetRenderer(), &box);
}

void Enemy::Update(float dt)
{
	// axis X
	m_RigidBody->Update(dt);
	m_lastSafePos.X = m_pTransform->X;
	m_pTransform->X += m_RigidBody->getPosition().X;
	m_Collider->Set(m_pTransform->X, m_pTransform->Y, 96, 96);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
	{
		m_pTransform->X = m_lastSafePos.X;
	}

	// axis Y

	m_RigidBody->Update(dt);
	m_lastSafePos.Y = m_pTransform->Y;
	m_pTransform->Y += m_RigidBody->getPosition().Y;
	m_Collider->Set(m_pTransform->X, m_pTransform->Y, 96, 96);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
	{
		m_pTransform->Y = m_lastSafePos.Y;
	}

	m_Animation->Update(dt);
	
}

void Enemy::Clean()
{

}