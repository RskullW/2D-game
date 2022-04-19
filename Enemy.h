#pragma once
#include "Character.h"
#include "RigdBody.h"
#include "Collider.h"
#include "SeqAnim.h"
#include "SpriteAnim.h"

class Enemy
	:public Character
{
public:
	Enemy(Properties* props);

	virtual void Draw();
	virtual void Clean();	
	virtual void Update(float dt);

private:
	Collider* m_Collider;
	RigdBody* m_RigidBody;
	SpriteAnim* m_Animation;
	Vector2D m_lastSafePos;
};

