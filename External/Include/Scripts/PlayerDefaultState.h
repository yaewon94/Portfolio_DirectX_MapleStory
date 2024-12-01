#pragma once
#include "Engine/State.h"

class PlayerDefaultState final : public State
{
	NO_COPY_MOVE(PlayerDefaultState);

public:
	PlayerDefaultState(FSM* const fsm);
	~PlayerDefaultState();

protected:
	virtual void OnStateEnter() final
	{
	}

private: // FSM::복사생성자 에서 호출
	PlayerDefaultState(const PlayerDefaultState& origin, FSM* const newOwner);
	virtual PlayerDefaultState* const Clone(FSM* const newOwner) final { return new PlayerDefaultState(*this, newOwner); }
};