#include "pch.h"
#include "PlayerDeadState.h"
#include "Engine/GameObject.h"
#include "Engine/FSM.h"
#include "Engine/Collider.h"
#include "Engine/FlipbookPlayer.h"

PlayerDeadState::PlayerDeadState(FSM* const fsm) 
	: State(fsm)
{
}

PlayerDeadState::PlayerDeadState(const PlayerDeadState& origin, FSM* const newOwner) 
	: State(origin, newOwner)
{
}

PlayerDeadState::~PlayerDeadState()
{
}

void PlayerDeadState::OnStateEnter()
{
	GetFSM()->GetOwner()->GetCollider()->SetActive(false);

	FlipbookPlayer* flipbookPlayer = GetFSM()->GetOwner()->GetComponent<FlipbookPlayer>();
	flipbookPlayer->ChangeFlipbook("Dead", true);
}