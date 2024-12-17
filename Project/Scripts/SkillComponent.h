#pragma once
#include "Engine/Script.h"
#include "IMovable.h"

class Skill;
class AliveObject;

// 스킬 컴포넌트 최상위 클래스
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

protected: // GameObject : Component* 를 통해 호출
	virtual void Init() final;

public:
	void SetCaster(AliveObject* const caster) { m_caster = caster; }

protected:
	AliveObject* const GetCaster() { return m_caster; }

	FlipbookPlayer* const GetFlipbookPlayer() { return m_flipbookPlayer; }
	void SetSkill(SharedPtr<Skill> skill)
	{
		m_flipbookPlayer->Clear();
		m_flipbookPlayer->AddFlipbook(skill->GetKey(), skill->GetFlipbook());
	}
};