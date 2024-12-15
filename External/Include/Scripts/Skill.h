#pragma once
#include "Engine/CustomAsset.h"

class AliveObject;
class SkillComponent;

// 스킬 에셋 최상위 클래스
class Skill : public CustomAsset
{
	NO_COPY_MOVE(Skill)

protected:
	SharedPtr<Flipbook> m_flipbook;
	string m_casterFlipbookKey; // 스킬 발동시, 재생할 애니메이션 키값 (스킬시전자)

protected:
	Skill(const string& Key, const string& relativePath);
	~Skill();

public:
	virtual void Execute(AliveObject* const caster, SkillComponent* const skillComponent) = 0;

public:
	SharedPtr<Flipbook> GetFlipbook() const { return m_flipbook; }
};