#pragma once
#include "Engine/State.h"

class MonsterDefaultState final : public State
{
	NO_COPY_MOVE(MonsterDefaultState);

public:
	MonsterDefaultState(FSM* const fsm);
	~MonsterDefaultState();

private: // FSM* Ŭ�������� state* �� ȣ��
	virtual void OnStateEnter() final;

private: // FSM::��������� ���� ȣ��
	MonsterDefaultState(const MonsterDefaultState& origin, FSM* const newOwner);
	virtual MonsterDefaultState* const Clone(FSM* const newOwner) final { return new MonsterDefaultState(*this, newOwner); }
};