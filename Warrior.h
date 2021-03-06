#pragma once
#include "Character.h"
#include "Animation.h"
#include "RigdBody.h"
#include "Collider.h"
#include "Vector2D.h"
#include "SpriteAnim.h"
#include "Enemy.h"
#include "Bullet.h"
#include "nameBar.h"


//#define JUMP_TIME 10.0f;
//#define JUMP_FORCE 7.0f

//#define RUN_FORCE 1.5f
#define ATTACK_TIME 20.0f

inline bool userButEscape = false;

class Warrior:
	public Character
{
public:
	Warrior(Properties* props);
	
	virtual void Draw();
    virtual void DrawDeath(std::string nameSound);

	virtual void Clean();
	virtual void Update(float dt);
	virtual void CheatSpeed();
	virtual void CheatJump();

	void clearInputCheats(bool*, int);

    virtual float& GetHealth() {return m_Health;}


private:

	struct enterCheats
	{
		bool numCheats[7];
		bool cheatActivated;
		int cntButton;
	};

	void AnimationState();
    void AnimationHPBAR();

    bool m_Jumping, m_Grounded, isFailing, m_Attacking;
	bool m_Running, m_JumpDown;

    bool m_sendNick;
	
	enterCheats hackSpeed, hackJump;

	float m_AccelarationFactorJump;
	float m_JumpTime, m_JumpForce, m_AttackTime, thisRunning;

    float m_Health, m_Damage;

	Collider* m_Collider;

	SpriteAnim* m_Animation;
    SpriteAnim* m_AnimationHP;

	RigdBody* m_RigidBody;

	Vector2D m_LastSafePos;
    Vector2D cam;

    Namebar* m_namebar;

};

