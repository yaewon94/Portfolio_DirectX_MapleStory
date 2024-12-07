#pragma once
#include "Component.h"

class Skill;

// ��ų ������Ʈ
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

private: // GameObject : Component* �� ���� ȣ��
	virtual void Init() final;
	virtual void FinalTick() final;

private: // GameObject::��������� ���� ȣ��
	virtual SkillComponent* Clone(GameObject* const newOwner) final { return new SkillComponent(*this, newOwner); }
};