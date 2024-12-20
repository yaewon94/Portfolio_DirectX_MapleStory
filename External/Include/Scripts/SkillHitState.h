#pragma once
#include "Engine/State.h"

class SkillHitState final : public State
{
	NO_COPY_MOVE(SkillHitState);

public:
	SkillHitState(FSM* const fsm);
	~SkillHitState();

private: // FSM* 클래스에서 state* 로 호출
	virtual void OnStateEnter() final;

private: // FSM::복사생성자 에서 호출
	SkillHitState(const SkillHitState& origin, FSM* const newOwner);
	virtual SkillHitState* const Clone(FSM* const newOwner) final { return new SkillHitState(*this, newOwner); }
};