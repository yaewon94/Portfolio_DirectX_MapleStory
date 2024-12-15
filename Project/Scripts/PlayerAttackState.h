#pragma once
#include "Engine/State.h"

class PlayerAttackState final : public State
{
	NO_COPY_MOVE(PlayerAttackState);

private:
	class FlipbookPlayer* m_flipbookPlayer;

public:
	PlayerAttackState(FSM* const fsm);
	~PlayerAttackState();

private: // FSM Ŭ�������� State* �� ȣ��
	virtual void OnStateTick() final;

private: // FSM::��������� ���� ȣ��
	PlayerAttackState(const PlayerAttackState& origin, FSM* const newOwner);
	virtual PlayerAttackState* const Clone(FSM* const newOwner) final { return new PlayerAttackState(*this, newOwner); }
};