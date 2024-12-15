#pragma once
#include "Engine/CustomAsset.h"
#include "Engine/Flipbook.h"

class AliveObject;

// ��ų ���� �ֻ��� Ŭ����
class Skill : public CustomAsset
{
	NO_COPY_MOVE(Skill)

protected:
	SharedPtr<Flipbook> m_flipbook; // ��ų �ִϸ��̼�
	string m_casterFlipbookKey; // ��ų ������ �ִϸ��̼� Ű��

protected:
	Skill(const string& Key, const string& relativePath);
	~Skill();

public:
	virtual void Execute(AliveObject* const caster, GameObject* const skillObj) = 0;

public:
	SharedPtr<Flipbook> GetFlipbook() const { return m_flipbook; }
};