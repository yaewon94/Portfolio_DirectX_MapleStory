#include "pch.h"
#include "PlayerMoveState.h"
#include "Engine/GameObject.h"
#include "Engine/FSM.h"
#include "Engine/FlipbookPlayer.h"

PlayerMoveState::PlayerMoveState(FSM* const fsm) 
	: State(fsm)
{
}

PlayerMoveState::PlayerMoveState(const PlayerMoveState& origin, FSM* const newOwner) 
	: State(origin, newOwner)
{
}

PlayerMoveState::~PlayerMoveState()
{
}

void PlayerMoveState::OnStateEnter()
{
	GetFSM()->GetOwner()->GetComponent<FlipbookPlayer>()->ChangeFlipbook("Move", false);
}