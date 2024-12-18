#include "pch.h"
#include "Monster.h"
#include "MonsterDefaultState.h"
#include "MonsterDeadState.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/FlipbookPlayer.h"
#include "Engine/Collider.h"
#include "Engine/FSM.h"

Monster::Monster(GameObject* const owner) 
	: AliveObject(owner)
{
	// ������Ʈ �߰�
	m_flipbookPlayer = GetOwner()->AddComponent<FlipbookPlayer>();
	GetOwner()->AddComponent<Collider>();
	m_fsm = GetOwner()->AddComponent<FSM>();
	m_fsm->AddState<MonsterDefaultState>(STATE_TYPE::DEFAULT);
	m_fsm->AddState<MonsterDeadState>(STATE_TYPE::DEAD);
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

	// �ν��Ͻ� ���� �ʵ� �ʱ�ȭ
	GetOwner()->SetTag(OBJECT_TAG::TAG_MONSTER);
	m_fsm->ChangeState(STATE_TYPE::DEFAULT);
}

void Monster::OnCollisionEnter(GameObject* other)
{
}
