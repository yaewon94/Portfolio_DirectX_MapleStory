#pragma once
#include "SkillComponent.h"
#include "IMovable.h"

// ��ų ������Ʈ
class AttackSkillComponent final : public SkillComponent, public IMovable
{
	NO_COPY_MOVE(AttackSkillComponent)

private:
	SharedPtr<AttackSkill> m_skill;
	Vec3 m_startPos;

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
	void SetSkill(SharedPtr<AttackSkill> skill)
	{
		if (m_skill != skill)
		{
			m_skill = skill;
			SkillComponent::SetSkill(skill.ptr_dynamic_cast<Skill>());
		}
	}

private: // GameObject::��������� ���� ȣ��
	virtual AttackSkillComponent* Clone(GameObject* const newOwner) final { return new AttackSkillComponent(*this, newOwner); }
};

///////////////////////////////////////////////////
// AttackSkillComponent.inl
///////////////////////////////////////////////////
#include "Engine/TimeManager.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
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