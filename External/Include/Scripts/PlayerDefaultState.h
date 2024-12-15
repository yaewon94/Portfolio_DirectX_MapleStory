#pragma once
#include "Engine/State.h"

class PlayerDefaultState final : public State
{
	NO_COPY_MOVE(PlayerDefaultState);

public:
	PlayerDefaultState(FSM* const fsm);
	~PlayerDefaultState();

private: // FSM* Ŭ�������� state* �� ȣ��
	virtual void OnStateEnter() final;

private: // FSM::��������� ���� ȣ��
	PlayerDefaultState(const PlayerDefaultState& origin, FSM* const newOwner);
	virtual PlayerDefaultState* const Clone(FSM* const newOwner) final { return new PlayerDefaultState(*this, newOwner); }
};