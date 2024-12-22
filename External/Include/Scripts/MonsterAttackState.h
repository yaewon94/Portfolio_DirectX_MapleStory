#pragma once
#include "Engine/State.h"

class MonsterAttackState final : public State
{
	NO_COPY_MOVE(MonsterAttackState);

private:
	class GameObject* m_skillObj;
	SharedPtr<AttackSkill> m_skill;
	float m_accTime;
	bool m_isSkillUsed;

public:
	MonsterAttackState(FSM* const fsm);
	~MonsterAttackState();

private: // FSM* 클래스에서 state* 로 호출
	virtual void OnStateEnter() final;
	virtual void OnStateTick() final;

private: // FSM::복사생성자 에서 호출
	MonsterAttackState(const MonsterAttackState& origin, FSM* const newOwner);
	virtual MonsterAttackState* const Clone(FSM* const newOwner) final { return new MonsterAttackState(*this, newOwner); }
};