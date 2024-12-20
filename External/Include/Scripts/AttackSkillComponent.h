#pragma once
#include "SkillComponent.h"
#include "AttackSkill.h"

typedef Power Damage;

// ��ų ������Ʈ
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

private: // GameObject : Component* �� ���� ȣ��
	virtual void FinalTick() final;
	virtual void SetActive(bool flag) final;

private:
	virtual void Move(MOVE_DIRECTION dir) final;

public:
	SharedPtr<AttackSkill> GetSkill() const { return m_skill; }
	void SetSkill(SharedPtr<AttackSkill> skill);

	Damage GetDamage() const;

private: // GameObject::��������� ���� ȣ��
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

	// �ִ� �̵������� ����� �ڵ� ��Ȱ��ȭ
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