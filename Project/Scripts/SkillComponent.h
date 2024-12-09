#pragma once
#include "Engine/Script.h"

class Skill;

// ��ų ������Ʈ
class SkillComponent final : public Script
{
	NO_COPY_MOVE(SkillComponent)

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