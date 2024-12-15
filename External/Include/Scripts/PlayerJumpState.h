#pragma once
#include "Engine/State.h"

class PlayerJumpState final : public State
{
	NO_COPY_MOVE(PlayerJumpState);

public:
	PlayerJumpState(FSM* const fsm);
	~PlayerJumpState();

private: // FSM* Ŭ�������� state* �� ȣ��
	virtual void OnStateEnter() final;

private: // FSM::��������� ���� ȣ��
	PlayerJumpState(const PlayerJumpState& origin, FSM* const newOwner);
	virtual PlayerJumpState* const Clone(FSM* const newOwner) final { return new PlayerJumpState(*this, newOwner); }
};