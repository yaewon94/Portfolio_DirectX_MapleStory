#pragma once
#include "SkillComponent.h"

// 스킬 컴포넌트
class AttackSkillComponent final : public SkillComponent
{
	NO_COPY_MOVE(AttackSkillComponent)

private:
	SharedPtr<AttackSkill> m_skill;

public:
	AttackSkillComponent(GameObject* const owner);
	AttackSkillComponent(const AttackSkillComponent& origin, GameObject* const newOwner);
	~AttackSkillComponent();

private: // GameObject : Component* 를 통해 호출
	virtual void FinalTick() final;
	virtual void SetActive(bool flag) final;

public:
	void SetSkill(SharedPtr<AttackSkill> skill)
	{
		if (m_skill != skill) SkillComponent::SetSkill(skill.ptr_dynamic_cast<Skill>());
	}

private: // GameObject::복사생성자 에서 호출
	virtual AttackSkillComponent* Clone(GameObject* const newOwner) final { return new AttackSkillComponent(*this, newOwner); }
};