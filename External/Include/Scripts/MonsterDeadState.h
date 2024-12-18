#pragma once
#include "Engine/State.h"

class MonsterDeadState final : public State
{
	NO_COPY_MOVE(MonsterDeadState);

public:
	MonsterDeadState(FSM* const fsm);
	~MonsterDeadState();

private: // FSM* 클래스에서 state* 로 호출
	virtual void OnStateEnter() final;

private: // FSM::복사생성자 에서 호출
	MonsterDeadState(const MonsterDeadState& origin, FSM* const newOwner);
	virtual MonsterDeadState* const Clone(FSM* const newOwner) final { return new MonsterDeadState(*this, newOwner); }
};