#include "pch.h"
#include "SkillDefaultState.h"
#include "AttackSkillComponent.h"
#include "Engine/GameObject.h"
#include "Engine/FSM.h"
#include "Engine/FlipbookPlayer.h"

SkillDefaultState::SkillDefaultState(FSM* const fsm) 
	: State(fsm)
{
}

SkillDefaultState::SkillDefaultState(const SkillDefaultState& origin, FSM* const newOwner) 
	: State(origin, newOwner)
{
}

SkillDefaultState::~SkillDefaultState()
{
}

void SkillDefaultState::Init()
{
	GameObject* obj = GetFSM()->GetOwner();
	m_flipbookPlayer = obj->GetComponent<FlipbookPlayer>();
	m_skillComponent = obj->GetComponent<AttackSkillComponent>();
}

void SkillDefaultState::OnStateEnter()
{
	m_flipbookPlayer->ChangeFlipbook(m_skillComponent->GetSkill()->GetFlipbook()->GetKey(), true);
	m_flipbookPlayer->SetRepeat(true);
}