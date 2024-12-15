#include "pch.h"
#include "PlayerDefaultState.h"
#include "Engine/GameObject.h"
#include "Engine/FSM.h"
#include "Engine/FlipbookPlayer.h"

PlayerDefaultState::PlayerDefaultState(FSM* const fsm) 
	: State(fsm)
{
}

PlayerDefaultState::PlayerDefaultState(const PlayerDefaultState& origin, FSM* const newOwner) 
	: State(origin, newOwner)
{
}

PlayerDefaultState::~PlayerDefaultState()
{
}

void PlayerDefaultState::OnStateEnter()
{
	GetFSM()->GetOwner()->GetComponent<FlipbookPlayer>()->ChangeFlipbook("Idle");
}