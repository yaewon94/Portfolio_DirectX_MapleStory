#pragma once
#include "Component.h"

// ���ӿ�����Ʈ ���� ���� ������Ʈ
class Rigidbody final : public Component
{
	NO_COPY_MOVE(Rigidbody)
	COMPONENT_TYPE_DCL(COMPONENT_TYPE::RIGIDBODY)

private:
	Vec3 m_velocity; // ���� �������� �ӵ�(�ӷ� * ���⺤��)
	float m_mass; // ����

	Vec3 m_gravityDelta;
	bool m_useGravity;

public:
	Rigidbody(GameObject* const owner);
	Rigidbody(const Rigidbody& origin, GameObject* const newOwner);
	~Rigidbody();

private: // GameObject : Component* �� ���� ȣ��
	virtual void Init() final;
	virtual void FinalTick() final;

public:
	void AddForce(const Vec3& force) { m_velocity += force; }

	void UseGravity(bool flag)
	{
		m_useGravity = flag;
		if (!flag) m_velocity = Vec3();
	}

	float GetMass() const { return m_mass; }
	void SetMass(float mass)
	{
		m_mass = mass;
		m_gravityDelta = Vec3(0.f, -1.f * m_mass * 9.8f, 0.f);
	}

private:
	virtual Rigidbody* Clone(GameObject* const newOwner) final { return new Rigidbody(*this, newOwner); }
};