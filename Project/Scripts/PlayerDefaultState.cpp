#include "pch.h"
#include "PlayerDefaultState.h"

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
