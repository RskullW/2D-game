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

    virtual Vector2D getPosEnemy() {return m_lastSafePos;}
    virtual float& GetHealth() {return m_Health;}
    virtual bool GetNearPlayer() {return nearPlayer;}
    virtual bool& GetStartPhrase() {return startPhrase;}

private:
    void AnimationState();
private:

    bool nearPlayer = 0;
    bool startPhrase = 0;
    bool isFailing, m_Attacking, m_Running;

    float m_Health, m_Damage, m_AttackTime, thisRunning;

    Collider* m_Collider;
	RigdBody* m_RigidBody;
	SpriteAnim* m_Animation;
	Vector2D m_lastSafePos;
};