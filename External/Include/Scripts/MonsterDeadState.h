#pragma once
#include "Engine/State.h"

class MonsterDeadState final : public State
{
	NO_COPY_MOVE(MonsterDeadState);

public:
	MonsterDeadState(FSM* const fsm);
	~MonsterDeadState();

private: // FSM* Ŭ�������� state* �� ȣ��
	virtual void OnStateEnter() final;

private: // FSM::��������� ���� ȣ��
	MonsterDeadState(const MonsterDeadState& origin, FSM* const newOwner);
	virtual MonsterDeadState* const Clone(FSM* const newOwner) final { return new MonsterDeadState(*this, newOwner); }
};