#pragma once
#include "SkillComponent.h"
#include "AttackSkill.h"

typedef Power Damage;

// 스킬 컴포넌트
class AttackSkillComponent final : public SkillComponent
{
	NO_COPY_MOVE(AttackSkillComponent)

private:
	SharedPtr<AttackSkill> m_skill;
	Vec3 m_startPos;
	Damage damage;

public:
	AttackSkillComponent(GameObject* const owner);
	AttackSkillComponent(const AttackSkillComponent& origin, GameObject* const newOwner);
	~AttackSkillComponent();

private: // GameObject : Component* 를 통해 호출
	virtual void FinalTick() final;
	virtual void SetActive(bool flag) final;

private:
	virtual void Move(MOVE_DIRECTION dir) final;

public:
	SharedPtr<AttackSkill> GetSkill() const { return m_skill; }
	void SetSkill(SharedPtr<AttackSkill> skill);

	Damage GetDamage() const;

private: // GameObject::복사생성자 에서 호출
	virtual AttackSkillComponent* Clone(GameObject* const newOwner) final { return new AttackSkillComponent(*this, newOwner); }
};

///////////////////////////////////////////////////
// AttackSkillComponent.inl
///////////////////////////////////////////////////
#include "Engine/TimeManager.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/FSM.h"
#include "AliveObject.h"
inline void AttackSkillComponent::Move(MOVE_DIRECTION dir)
{
	Transform* tr = GetOwner()->GetTransform();
	Vec3 curPos = tr->GetLocalPos();

	// 최대 이동범위를 벗어나면 자동 비활성화
	if (Vec3::Distance(curPos, m_startPos) >= m_skill->GetMaxDistance())
	{
		GetOwner()->SetActive(false);
		return;
	}

	curPos += DT * m_skill->GetVelocity() * dir;
	tr->SetLocalPos(curPos);
}

inline void AttackSkillComponent::SetSkill(SharedPtr<AttackSkill> skill)
{
	if (m_skill != skill)
	{
		m_skill = skill;
		SkillComponent::SetSkill(skill.ptr_dynamic_cast<Skill>());
	}

	GetOwner()->GetComponent<FSM>()->ChangeState(STATE_TYPE::DEFAULT);
}

inline Damage AttackSkillComponent::GetDamage() const 
{ 
	return m_skill->GetCoefficient() * GetCaster()->GetPower();
}