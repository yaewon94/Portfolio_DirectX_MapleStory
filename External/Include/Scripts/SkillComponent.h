#pragma once
#include "Engine/Script.h"
#include "AliveObject.h"

class Skill;

// ��ų ������Ʈ �ֻ��� Ŭ����
class SkillComponent : public Script, public IMovable
{
	NO_COPY_MOVE(SkillComponent)

private:
	AliveObject* m_caster;
	class FlipbookPlayer* m_flipbookPlayer;

protected:
	SkillComponent(GameObject* const owner);
	SkillComponent(const SkillComponent& origin, GameObject* const newOwner);
	~SkillComponent();

protected: // GameObject : Component* �� ���� ȣ��
	virtual void Init() final;

public:
	void SetCaster(AliveObject* const caster) { m_caster = caster; }

protected:
	AliveObject* const GetCaster() const { return m_caster; }

	void SetSkill(SharedPtr<Skill> skill)
	{
		m_flipbookPlayer->Clear();
		m_flipbookPlayer->AddFlipbook(skill->GetKey(), skill->GetFlipbook());
	}
};