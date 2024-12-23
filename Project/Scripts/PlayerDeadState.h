#pragma once
#include "Engine/State.h"

class PlayerDeadState final : public State
{
	NO_COPY_MOVE(PlayerDeadState);

public:
	PlayerDeadState(FSM* const fsm);
	~PlayerDeadState();

private: // FSM* Ŭ�������� state* �� ȣ��
	virtual void OnStateEnter() final;

private: // FSM::��������� ���� ȣ��
	PlayerDeadState(const PlayerDeadState& origin, FSM* const newOwner);
	virtual PlayerDeadState* const Clone(FSM* const newOwner) final { return new PlayerDeadState(*this, newOwner); }
};