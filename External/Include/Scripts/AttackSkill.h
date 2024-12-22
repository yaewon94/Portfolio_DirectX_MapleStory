#pragma once
#include "Skill.h"

// 공격형 스킬
class AttackSkill final : public Skill
{
	NO_COPY_MOVE(AttackSkill)

private:
	float m_maxDistance;
	Vec3 m_velocity;
	float m_coefficient; // 데미지 계수
	float m_delay;	// 스킬 오브젝트가 활성화 되기까지 딜레이타임

public:
	AttackSkill(const string& Key, const string& relativePath);
	~AttackSkill();

public:
	virtual void Execute(AliveObject* const caster, GameObject* const skillObj) final;

private: // AssetManager에서 Asset* 으로 호출
	virtual int Load() final;

public:
	float GetMaxDistance() const { return m_maxDistance; }
	const Vec3& GetVelocity() const { return m_velocity; }
	float GetCoefficient() const { return m_coefficient; }
	float GetDelay() const { return m_delay; }
};