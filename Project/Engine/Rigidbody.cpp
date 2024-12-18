#include "pch.h"
#include "Rigidbody.h"
#include "TimeManager.h"
#include "Transform.h"
#include "GameObject.h"

Rigidbody::Rigidbody(GameObject* const owner) 
	: Component(owner)
	, m_mass(1.f)
{
}

Rigidbody::Rigidbody(const Rigidbody& origin, GameObject* const newOwner) 
	: Component(origin, newOwner)
	, m_mass(origin.m_mass)
{
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::Init()
{
	m_useGravity = false;
	SetMass(m_mass);
}

void Rigidbody::FinalTick()
{
	// 이렇게 체크하면 안됨
	// 점프하다가 velocity.y값 떨어지는 와중에 velocity가 0이 되는경우 나올수도 있으니까
	//if (m_velocity == Vec3(0.f, 0.f, 0.f)) return;

	// 중력 방향으로 가속도 적용
	if (m_useGravity)
	{
		Vec3 pos = GetOwner()->GetTransform()->GetLocalPos();
		m_velocity += m_gravityDelta;
		GetOwner()->GetTransform()->SetLocalPos(pos + m_velocity * DT);
	}
}
