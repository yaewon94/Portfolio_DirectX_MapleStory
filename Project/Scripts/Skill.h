#pragma once
#include "Engine/CustomAsset.h"

// ��ų ���� �ֻ��� Ŭ����
class Skill : public CustomAsset
{
	NO_COPY_MOVE(Skill)

private:
	string m_name;

protected:
	Skill(const string& Key, const string& relativePath);
	~Skill();

public:
	virtual void Execute(class SkillComponent* component) = 0;

protected:
	const string& GetName() const { return m_name; }
	void SetName(const string& name) { m_name = name; }
};