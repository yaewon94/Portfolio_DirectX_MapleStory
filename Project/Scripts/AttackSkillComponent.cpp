#include "pch.h"
#include "AttackSkillComponent.h"
#include "AliveObject.h"
#include "AttackSkill.h"
#include "Engine/FlipbookPlayer.h"

AttackSkillComponent::AttackSkillComponent(GameObject* const owner) 
	: SkillComponent(owner)
{
	Init();
}

AttackSkillComponent::AttackSkillComponent(const AttackSkillComponent& origin, GameObject* const newOwner) 
	: SkillComponent(origin ,newOwner)
{
	Init();
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