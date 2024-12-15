#pragma once
#include "Skill.h"

// 공격형 스킬
class AttackSkill final : public Skill
{
	NO_COPY_MOVE(AttackSkill)

public:
	AttackSkill(const string& Key, const string& relativePath);
	~AttackSkill();

public:
	virtual void Execute(AliveObject* const caster, GameObject* const skillObj) final;

private: // AssetManager에서 Asset* 으로 호출
	virtual int Load() final;
};