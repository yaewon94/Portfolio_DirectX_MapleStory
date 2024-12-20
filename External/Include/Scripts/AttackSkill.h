#pragma once
#include "Skill.h"

// ������ ��ų
class AttackSkill final : public Skill
{
	NO_COPY_MOVE(AttackSkill)

private:
	float m_maxDistance;
	Vec3 m_velocity;
	float m_coefficient; // ������ ���

public:
	AttackSkill(const string& Key, const string& relativePath);
	~AttackSkill();

public:
	virtual void Execute(AliveObject* const caster, GameObject* const skillObj) final;

private: // AssetManager���� Asset* ���� ȣ��
	virtual int Load() final;

public:
	float GetMaxDistance() const { return m_maxDistance; }
	const Vec3& GetVelocity() const { return m_velocity; }
	float GetCoefficient() const { return m_coefficient; }
};