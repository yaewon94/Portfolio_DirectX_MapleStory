#include "pch.h"
#include "PlayerAttackState.h"
#include "Engine/GameObject.h"
#include "Engine/FSM.h"
#include "Engine/FlipbookPlayer.h"

PlayerAttackState::PlayerAttackState(FSM* const fsm)
	: State(fsm)
	, m_flipbookPlayer(fsm->GetOwner()->GetComponent<FlipbookPlayer>())
{
}

PlayerAttackState::PlayerAttackState(const PlayerAttackState& origin, FSM* const newOwner) 
	: State(origin, newOwner)
	, m_flipbookPlayer(newOwner->GetOwner()->GetComponent<FlipbookPlayer>())
{
}


PlayerAttackState::~PlayerAttackState()
{
}

void PlayerAttackState::OnStateTick()
{
	if (m_flipbookPlayer->IsFinish()) GetFSM()->ChangeState(STATE_TYPE::DEFAULT);
}