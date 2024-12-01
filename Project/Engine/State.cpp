#include "pch.h"
#include "State.h"

State::State(FSM* const fsm) 
	: m_fsm(fsm)
{
}

State::State(const State& origin, FSM* const newOwner) 
	: m_fsm(newOwner)
{
}

State::~State()
{
}
