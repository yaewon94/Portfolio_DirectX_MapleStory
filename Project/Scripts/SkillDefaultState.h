#pragma once
#include "Engine/State.h"

class SkillDefaultState final : public State
{
	NO_COPY_MOVE(SkillDefaultState);

private:
	class FlipbookPlayer* m_flipbookPlayer;
	class AttackSkillComponent* m_skillComponent;

public:
	SkillDefaultState(FSM* const fsm);
	~SkillDefaultState();

private: // FSM* 클래스에서 state* 로 호출
	virtual void Init() final;
	virtual void OnStateEnter() final;

private: // FSM::복사생성자 에서 호출
	SkillDefaultState(const SkillDefaultState& origin, FSM* const newOwner);
	virtual SkillDefaultState* const Clone(FSM* const newOwner) final { return new SkillDefaultState(*this, newOwner); }
};