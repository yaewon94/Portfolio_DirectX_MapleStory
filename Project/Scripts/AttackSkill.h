#pragma once
#include "Skill.h"

// ������ ��ų
class AttackSkill final : public Skill
{
	NO_COPY_MOVE(AttackSkill)

public:
	AttackSkill(const string& Key, const string& relativePath);
	~AttackSkill();

public:
	virtual void Execute(AliveObject* const caster, SkillComponent* const skillComponent) final;

private: // AssetManager���� Asset* ���� ȣ��
	virtual int Load() final;
};