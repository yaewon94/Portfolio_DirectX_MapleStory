#include "pch.h"
#include "SkillHitState.h"
#include "Engine/GameObject.h"
#include "Engine/FSM.h"

SkillHitState::SkillHitState(FSM* const fsm) 
	: State(fsm)
{
}

SkillHitState::SkillHitState(const SkillHitState& origin, FSM* const newOwner) 
	: State(origin, newOwner)
{
}


SkillHitState::~SkillHitState()
{
}

void SkillHitState::OnStateEnter()
{
	GetFSM()->GetOwner()->SetActive(false);
}