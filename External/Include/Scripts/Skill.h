#pragma once
#include "Engine/CustomAsset.h"

class AliveObject;
class GameObject;

// 스킬 에셋 최상위 클래스
class Skill : public CustomAsset
{
	NO_COPY_MOVE(Skill)

private:
	string m_name;

protected:
	Skill(const string& Key, const string& relativePath);
	~Skill();

public:
	virtual void Execute(AliveObject* const caster, GameObject* const skillObj) = 0;

protected:
	const string& GetName() const { return m_name; }
	void SetName(const string& name) { m_name = name; }
};