#pragma once
#include "Engine/State.h"

class SkillHitState final : public State
{
	NO_COPY_MOVE(SkillHitState);

public:
	SkillHitState(FSM* const fsm);
	~SkillHitState();

private: // FSM* Ŭ�������� state* �� ȣ��
	virtual void OnStateEnter() final;

private: // FSM::��������� ���� ȣ��
	SkillHitState(const SkillHitState& origin, FSM* const newOwner);
	virtual SkillHitState* const Clone(FSM* const newOwner) final { return new SkillHitState(*this, newOwner); }
};