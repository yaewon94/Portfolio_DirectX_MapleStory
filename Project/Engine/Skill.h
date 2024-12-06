#pragma once
#include "Asset.h"

// 스킬 에셋 최상위 클래스
class Skill : public Asset
{
	NO_COPY_MOVE(Skill)
	ASSET_TYPE_DCL(ASSET_TYPE::SKILL)

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