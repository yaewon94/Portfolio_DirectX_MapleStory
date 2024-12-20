#include "pch.h"
#include "MonsterDeadState.h"
#include "Engine/GameObject.h"
#include "Engine/FSM.h"
#include "Engine/FlipbookPlayer.h"

MonsterDeadState::MonsterDeadState(FSM* const fsm) 
	: State(fsm)
{
}

MonsterDeadState::MonsterDeadState(const MonsterDeadState& origin, FSM* const newOwner) 
	: State(origin, newOwner)
{
}

MonsterDeadState::~MonsterDeadState()
{
}

void MonsterDeadState::OnStateEnter()
{
	GetFSM()->GetOwner()->GetCollider()->SetActive(false);

	FlipbookPlayer* flipbookPlayer = GetFSM()->GetOwner()->GetComponent<FlipbookPlayer>();
	flipbookPlayer->ChangeFlipbook("Dead", true);
	flipbookPlayer->SetRepeat(false);
}