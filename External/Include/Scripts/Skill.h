#pragma once
#include "Engine/CustomAsset.h"
#include "Engine/Flipbook.h"

class AliveObject;

// 스킬 에셋 최상위 클래스
class Skill : public CustomAsset
{
	NO_COPY_MOVE(Skill)

protected:
	SharedPtr<Flipbook> m_flipbook; // 스킬 애니메이션
	string m_casterFlipbookKey; // 스킬 시전자 애니메이션 키값

protected:
	Skill(const string& Key, const string& relativePath);
	~Skill();

public:
	virtual void Execute(AliveObject* const caster, GameObject* const skillObj) = 0;

public:
	SharedPtr<Flipbook> GetFlipbook() const { return m_flipbook; }
};