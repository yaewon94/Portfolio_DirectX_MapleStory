#pragma once
#include "Engine/State.h"

class PlayerMoveState final : public State
{
	NO_COPY_MOVE(PlayerMoveState);

public:
	PlayerMoveState(FSM* const fsm);
	~PlayerMoveState();

private: // FSM* Ŭ�������� state* �� ȣ��
	virtual void OnStateEnter() final;

private: // FSM::��������� ���� ȣ��
	PlayerMoveState(const PlayerMoveState& origin, FSM* const newOwner);
	virtual PlayerMoveState* const Clone(FSM* const newOwner) final { return new PlayerMoveState(*this, newOwner); }
};