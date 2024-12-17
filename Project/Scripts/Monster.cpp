#include "pch.h"
#include "Monster.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/FlipbookPlayer.h"
#include "Engine/Collider.h"
#include "Engine/FSM.h"

Monster::Monster(GameObject* const owner) 
	: AliveObject(owner)
{
	// 몬스터 기본 컴포넌트 추가
	// FlipbookPlayer (Render Component)
	m_flipbookPlayer = GetOwner()->AddComponent<FlipbookPlayer>();
	// Collider
	Collider* collider = GetOwner()->AddComponent<Collider>();
	collider->SetScale(Vec2(0.2f, 0.3f));
	// fsm
	m_fsm = GetOwner()->AddComponent<FSM>();

	Init();
}

Monster::Monster(const Monster& origin, GameObject* const newOwner) 
	: AliveObject(origin, newOwner)
{
	Init();
}

Monster::~Monster()
{
}

void Monster::Init()
{
	AliveObject::Init();

	// 인스턴스 공통 필드 초기화
	GetOwner()->GetTransform()->SetLocalScale(Vec3(200.f, 200.f, 1.f));
	GetOwner()->SetTag(OBJECT_TAG::TAG_MONSTER);
}

void Monster::OnCollisionEnter(GameObject* other)
{
}
