#include "pch.h"
#include "PlayerJumpState.h"
#include "Engine/GameObject.h"
#include "Engine/FSM.h"
#include "Engine/FlipbookPlayer.h"

PlayerJumpState::PlayerJumpState(FSM* const fsm) 
	: State(fsm)
{
}

PlayerJumpState::PlayerJumpState(const PlayerJumpState& origin, FSM* const newOwner) 
	: State(origin, newOwner)
{
}

PlayerJumpState::~PlayerJumpState()
{
}

void PlayerJumpState::OnStateEnter()
{
	GetFSM()->GetOwner()->GetComponent<FlipbookPlayer>()->ChangeFlipbook("Jump");
}