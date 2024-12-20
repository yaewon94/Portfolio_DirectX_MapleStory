#include "pch.h"
#include "AttackSkillComponent.h"
#include "AliveObject.h"
#include "SkillDefaultState.h"
#include "SkillHitState.h"
#include "Engine/FlipbookPlayer.h"
#include "Engine/Collider.h"

AttackSkillComponent::AttackSkillComponent(GameObject* const owner) 
	: SkillComponent(owner)
{
	GetOwner()->AddComponent<Collider>();
	FSM* fsm = GetOwner()->AddComponent<FSM>();
	fsm->AddState<SkillDefaultState>(STATE_TYPE::DEFAULT);
	fsm->AddState<SkillHitState>(STATE_TYPE::HIT);
}

AttackSkillComponent::AttackSkillComponent(const AttackSkillComponent& origin, GameObject* const newOwner) 
	: SkillComponent(origin ,newOwner)
{
}

AttackSkillComponent::~AttackSkillComponent()
{
}

void AttackSkillComponent::FinalTick()
{
	Move(m_moveDir);
}

void AttackSkillComponent::SetActive(bool flag)
{
	if (flag)
	{
#ifdef _DEBUG
		if (GetCaster() == nullptr) assert(nullptr);
#endif // _DEBUG

		m_moveDir = GetCaster()->GetMoveDirection();
		m_startPos = GetCaster()->GetOwner()->GetTransform()->GetLocalPos() + Vec3(100.f * m_moveDir, 0.f, 0.f);
		GetOwner()->GetTransform()->SetLocalPos(m_startPos);

		GetOwner()->GetRenderComponent()->GetConstBuffer().direction = (float)m_moveDir;
	}
}