#include "pch.h"
#include "Monster.h"
#include "MonsterDefaultState.h"
#include "MonsterDeadState.h"
#include "MonsterAttackState.h"
#include "Engine/LevelManager.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/FlipbookPlayer.h"
#include "Engine/Collider.h"
#include "Engine/FSM.h"
#include "Engine/TimeManager.h"
#include "Engine/RandomManager.h"

#define TERM_USE_SKILL 3.f

Monster::Monster(GameObject* const owner) 
	: AliveObject(owner)
{
	// 컴포넌트 추가
	m_flipbookPlayer = GetOwner()->AddComponent<FlipbookPlayer>();
	GetOwner()->AddComponent<Collider>();
	m_fsm = GetOwner()->AddComponent<FSM>();
	m_fsm->AddState<MonsterDefaultState>(STATE_TYPE::DEFAULT);
	m_fsm->AddState<MonsterDeadState>(STATE_TYPE::DEAD);
	m_fsm->AddState<MonsterAttackState>(STATE_TYPE::ATTACK);
}

Monster::Monster(const Monster& origin, GameObject* const newOwner) 
	: AliveObject(origin, newOwner)
{
}

Monster::~Monster()
{
}

void Monster::Init()
{
	AliveObject::Init();

	// 인스턴스 공통 필드 초기화
	GetOwner()->SetTag(OBJECT_TAG::TAG_MONSTER);
	m_fsm->ChangeState(STATE_TYPE::DEFAULT);
	m_accTime = 0.f;

	// 스킬오브젝트 추가 (자식 오브젝트로 생성 X)
	m_skillObj = LevelManager::GetInstance()->CreateObject("MonsterSkillObj");
	m_skillObj->SetTag(OBJECT_TAG::TAG_MONSTER_SKILL);
	m_skillObj->AddComponent<AttackSkillComponent>()->SetCaster(this);
	m_skillObj->Init();
}

void Monster::Tick()
{
	if (m_fsm->GetCurrentState() == STATE_TYPE::DEAD 
		|| m_fsm->GetCurrentState() == STATE_TYPE::ATTACK) return;

	m_accTime += DT;

	// 스킬 무작위 사용
	if (m_accTime > TERM_USE_SKILL)
	{
		m_skills[RandomManager::GetInstance()->GetRandom(0, m_skills.size()-1)]->Execute(this, m_skillObj);
		m_accTime -= TERM_USE_SKILL;
	}
}