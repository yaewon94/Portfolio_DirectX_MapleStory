#pragma once
#include "Engine/State.h"

class MonsterDefaultState final : public State
{
	NO_COPY_MOVE(MonsterDefaultState);

public:
	MonsterDefaultState(FSM* const fsm);
	~MonsterDefaultState();

private: // FSM* 클래스에서 state* 로 호출
	virtual void OnStateEnter() final;

private: // FSM::복사생성자 에서 호출
	MonsterDefaultState(const MonsterDefaultState& origin, FSM* const newOwner);
	virtual MonsterDefaultState* const Clone(FSM* const newOwner) final { return new MonsterDefaultState(*this, newOwner); }
};