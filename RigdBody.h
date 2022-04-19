#pragma once
#include "Vector2D.h"

#define MASSA 0.8f
#define GRAVITY 9.8f

#define FORWARD -1
#define BACKWARD 1

#define UPWARD -1
#define DOWNWARD 1

class RigdBody
{
private:
	float m_mass, m_gravity;
	Vector2D m_Force, m_Friction, m_Position, m_Velocity, m_Accelaration;
public:
	RigdBody()
	{
		m_mass = MASSA;
		m_gravity = GRAVITY;
	}

	inline void setMass(float mass) { m_mass = mass; }
	inline void setGravity(float gravity) { m_gravity = gravity; }

	inline void ApplyForce(Vector2D F) { m_Force = F; }
	inline void ApplyForceX(float x) { m_Force.X = x; }
	inline void ApplyForceY(float y) { m_Force.Y = y; }
	inline void UnSetForce() { m_Force = Vector2D(0, 0); }

	inline void ApplyFriction(Vector2D Fr) { m_Friction = Fr; }
	inline void ApplyFrictionX(float x) { m_Friction.X = x; }
	inline void ApplyFrictionY(float y) { m_Friction.Y = y; }
	inline void UnSetFriction() { m_Friction = Vector2D(0, 0); }

	inline float getMass() { return m_mass; }
	inline Vector2D getPosition() { return m_Position; }
	inline Vector2D getVelocity() { return m_Velocity; }
	inline Vector2D getAccelaration() { return m_Accelaration; }

	void Update(float dt)
	{
		m_Accelaration.X = (m_Force.X + m_Friction.X) / m_mass;
		m_Accelaration.Y = m_gravity + m_Force.Y/m_mass;
		m_Velocity = m_Accelaration/* *dt*/;
		m_Position.X = m_Velocity.X;
		m_Position.Y = m_Velocity.Y; /** dt*/
	}


};

