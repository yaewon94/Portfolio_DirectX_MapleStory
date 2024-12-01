#include "pch.h"
#include "State.h"

State::State() 
	: m_fsm(nullptr)
{
}

State::State(const State& origin, FSM* const owner) 
	: m_fsm(owner)
{
}

State::~State()
{
}
