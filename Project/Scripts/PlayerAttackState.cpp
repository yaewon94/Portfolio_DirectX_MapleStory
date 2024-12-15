#include "pch.h"
#include "PlayerAttackState.h"
#include "Engine/GameObject.h"
#include "Engine/FSM.h"
#include "Engine/FlipbookPlayer.h"

PlayerAttackState::PlayerAttackState(FSM* const fsm) 
	: State(fsm)
{
}

PlayerAttackState::PlayerAttackState(const PlayerAttackState& origin, FSM* const newOwner) 
	: State(origin, newOwner)
{
}


PlayerAttackState::~PlayerAttackState()
{
}

void PlayerAttackState::OnStateTick()
{
	GetFSM()->GetOwner()->GetComponent<FlipbookPlayer>()->IsFinish();
}