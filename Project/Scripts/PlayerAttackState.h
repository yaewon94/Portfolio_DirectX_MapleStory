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

private: // FSM 클래스에서 State* 로 호출
	virtual void OnStateTick() final;

private: // FSM::복사생성자 에서 호출
	PlayerAttackState(const PlayerAttackState& origin, FSM* const newOwner);
	virtual PlayerAttackState* const Clone(FSM* const newOwner) final { return new PlayerAttackState(*this, newOwner); }
};