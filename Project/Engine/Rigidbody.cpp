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
	// �̷��� üũ�ϸ� �ȵ�
	// �����ϴٰ� velocity.y�� �������� ���߿� velocity�� 0�� �Ǵ°�� ���ü��� �����ϱ�
	//if (m_velocity == Vec3(0.f, 0.f, 0.f)) return;

	// �߷� �������� ���ӵ� ����
	if (m_useGravity)
	{
		Vec3 pos = GetOwner()->GetTransform()->GetLocalPos();
		m_velocity += m_gravityDelta;
		GetOwner()->GetTransform()->SetLocalPos(pos + m_velocity * DT);
	}
}
