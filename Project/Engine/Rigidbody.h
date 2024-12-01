#pragma once
#include "Component.h"

// 게임오브젝트 물리 제어 컴포넌트
class Rigidbody final : public Component
{
	NO_COPY_MOVE(Rigidbody)
	COMPONENT_TYPE_DCL(COMPONENT_TYPE::RIGIDBODY)

private:
	Vec3 m_velocity; // 현재 프레임의 속도(속력 * 방향벡터)
	float m_mass; // 질량

	Vec3 m_gravityDelta;
	bool m_useGravity;

public:
	Rigidbody(GameObject* const owner);
	Rigidbody(const Rigidbody& origin, GameObject* const newOwner);
	~Rigidbody();

private: // GameObject : Component* 를 통해 호출
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