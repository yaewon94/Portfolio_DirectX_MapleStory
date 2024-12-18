#include "pch.h"
#include "MonsterDefaultState.h"
#include "Engine/GameObject.h"
#include "Engine/FSM.h"
#include "Engine/FlipbookPlayer.h"

MonsterDefaultState::MonsterDefaultState(FSM* const fsm) 
	: State(fsm)
{
}

MonsterDefaultState::MonsterDefaultState(const MonsterDefaultState& origin, FSM* const newOwner) 
	: State(origin, newOwner)
{
}

MonsterDefaultState::~MonsterDefaultState()
{
}

void MonsterDefaultState::OnStateEnter()
{
	FlipbookPlayer* flipbookPlayer = GetFSM()->GetOwner()->GetComponent<FlipbookPlayer>();
	flipbookPlayer->ChangeFlipbook("Idle");
	flipbookPlayer->SetRepeat(true);
}