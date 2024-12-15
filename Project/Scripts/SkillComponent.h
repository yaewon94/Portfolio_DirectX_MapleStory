#pragma once
#include "Engine/Script.h"

class Skill;

// ��ų ������Ʈ �ֻ��� Ŭ����
class SkillComponent : public Script
{
	NO_COPY_MOVE(SkillComponent)

private:
	GameObject* m_caster;
	class FlipbookPlayer* m_flipbookPlayer;

protected:
	SkillComponent(GameObject* const owner);
	SkillComponent(const SkillComponent& origin, GameObject* const newOwner);
	~SkillComponent();

protected: // GameObject : Component* �� ���� ȣ��
	virtual void Init() final;

public:
	void SetCaster(GameObject* const caster) { m_caster = caster; }

protected:
	GameObject* const GetCaster() { return m_caster; }

	FlipbookPlayer* const GetFlipbookPlayer() { return m_flipbookPlayer; }
	void SetSkill(SharedPtr<Skill> skill)
	{
		m_flipbookPlayer->Clear();
		m_flipbookPlayer->AddFlipbook(skill->GetKey(), skill->GetFlipbook());
	}
};