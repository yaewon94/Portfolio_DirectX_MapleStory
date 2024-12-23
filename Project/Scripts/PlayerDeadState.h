#pragma once
#include "Engine/State.h"

class PlayerDeadState final : public State
{
	NO_COPY_MOVE(PlayerDeadState);

public:
	PlayerDeadState(FSM* const fsm);
	~PlayerDeadState();

private: // FSM* 클래스에서 state* 로 호출
	virtual void OnStateEnter() final;

private: // FSM::복사생성자 에서 호출
	PlayerDeadState(const PlayerDeadState& origin, FSM* const newOwner);
	virtual PlayerDeadState* const Clone(FSM* const newOwner) final { return new PlayerDeadState(*this, newOwner); }
};