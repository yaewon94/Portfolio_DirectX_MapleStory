#include "pch.h"
#include "MonsterAttackState.h"
#include "Monster.h"
#include "AttackSkill.h"
#include "Engine/GameObject.h"
#include "Engine/FSM.h"
#include "Engine/FlipbookPlayer.h"
#include "Engine/TimeManager.h"

MonsterAttackState::MonsterAttackState(FSM* const fsm) 
	: State(fsm)
{
}

MonsterAttackState::MonsterAttackState(const MonsterAttackState& origin, FSM* const newOwner) 
	: State(origin, newOwner)
{
}

MonsterAttackState::~MonsterAttackState()
{
}

void MonsterAttackState::OnStateEnter()
{
	m_skill = SharedPtr<AttackSkill>(reinterpret_cast<AttackSkill*>(GetFSM()->GetStateData()));
	m_accTime = 0.f;
	m_isSkillUsed = false;
}

void MonsterAttackState::OnStateTick()
{
	if (m_isSkillUsed)
	{
		//if (!m_skillObj->IsActive()) GetFSM()->ChangeState(STATE_TYPE::DEFAULT);
	}
	else
	{
		m_accTime += DT;
		if (m_accTime >= m_skill->GetDelay())
		{
			m_skillObj = GetFSM()->GetOwner()->GetComponent<Monster>()->GetSkillObject();
			m_skillObj->GetComponent<AttackSkillComponent>()->SetSkill(m_skill);
			m_skillObj->SetActive(true);
			m_isSkillUsed = true;
		}
	}
}