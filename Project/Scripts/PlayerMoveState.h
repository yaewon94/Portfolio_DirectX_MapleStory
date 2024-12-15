#pragma once
#include "Engine/State.h"

class PlayerMoveState final : public State
{
	NO_COPY_MOVE(PlayerMoveState);

public:
	PlayerMoveState(FSM* const fsm);
	~PlayerMoveState();

private: // FSM* 클래스에서 state* 로 호출
	virtual void OnStateEnter() final;

private: // FSM::복사생성자 에서 호출
	PlayerMoveState(const PlayerMoveState& origin, FSM* const newOwner);
	virtual PlayerMoveState* const Clone(FSM* const newOwner) final { return new PlayerMoveState(*this, newOwner); }
};