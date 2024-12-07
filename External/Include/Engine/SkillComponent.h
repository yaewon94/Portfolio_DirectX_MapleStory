#pragma once
#include "Component.h"

class Skill;

// 스킬 컴포넌트
class SkillComponent final : public Component
{
	NO_COPY_MOVE(SkillComponent)
	COMPONENT_TYPE_DCL(COMPONENT_TYPE::SKILL)

private:
	SharedPtr<Skill> m_skill;

public:
	SkillComponent(GameObject* const owner);
	SkillComponent(const SkillComponent& origin, GameObject* const newOwner);
	~SkillComponent();

private: // GameObject : Component* 를 통해 호출
	virtual void Init() final;
	virtual void FinalTick() final;

private: // GameObject::복사생성자 에서 호출
	virtual SkillComponent* Clone(GameObject* const newOwner) final { return new SkillComponent(*this, newOwner); }
};