#pragma once
#include "Engine/State.h"

class PlayerJumpState final : public State
{
	NO_COPY_MOVE(PlayerJumpState);

public:
	PlayerJumpState(FSM* const fsm);
	~PlayerJumpState();

private: // FSM* 클래스에서 state* 로 호출
	virtual void OnStateEnter() final;

private: // FSM::복사생성자 에서 호출
	PlayerJumpState(const PlayerJumpState& origin, FSM* const newOwner);
	virtual PlayerJumpState* const Clone(FSM* const newOwner) final { return new PlayerJumpState(*this, newOwner); }
};