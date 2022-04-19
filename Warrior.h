#pragma once
#include "Character.h"
#include "Animation.h"
#include "RigdBody.h"
#include "Collider.h"
#include "Vector2D.h"
#include "SpriteAnim.h"

//#define JUMP_TIME 10.0f;
//#define JUMP_FORCE 7.0f

//#define RUN_FORCE 1.5f
#define ATTACK_TIME 20.0f

class Warrior:
	public Character
{
public:
	Warrior(Properties* props);
	
	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);
	virtual void CheatSpeed();
	virtual void CheatJump();
	void clearInputCheats(bool*, int);

private:

	struct enterCheats
	{
		bool numCheats[7];
		bool cheatActivated;
		int cntButton;
	};

	void AnimationState();

	bool m_Jumping;
	bool m_Grounded;
	bool isFailing;
	bool m_Attacking;
	bool m_Running;
	bool m_ShiftRun;
	bool m_JumpDown;
	
	enterCheats hackSpeed;
	enterCheats hackJump;

	float m_AccelarationFactorJump;
	float m_JumpTime;
	float m_JumpForce;
	float m_AttackTime;
	
	float thisRunning;

	Collider* m_Collider;

	SpriteAnim* m_Animation;
	RigdBody* m_RigidBody;

	Vector2D m_LastSafePos;

};

