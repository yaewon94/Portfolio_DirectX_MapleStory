#pragma once
#include "Engine/CustomAsset.h"

class AliveObject;
class SkillComponent;

// ��ų ���� �ֻ��� Ŭ����
class Skill : public CustomAsset
{
	NO_COPY_MOVE(Skill)

protected:
	SharedPtr<Flipbook> m_flipbook;
	string m_casterFlipbookKey; // ��ų �ߵ���, ����� �ִϸ��̼� Ű�� (��ų������)

protected:
	Skill(const string& Key, const string& relativePath);
	~Skill();

public:
	virtual void Execute(AliveObject* const caster, SkillComponent* const skillComponent) = 0;

public:
	SharedPtr<Flipbook> GetFlipbook() const { return m_flipbook; }
};