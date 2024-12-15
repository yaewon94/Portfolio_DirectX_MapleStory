#include "pch.h"
#include "AttackSkillComponent.h"
#include "AliveObject.h"
#include "Skill.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
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
}

void AttackSkillComponent::SetActive(bool flag)
{
	if (flag)
	{
#ifdef _DEBUG
		if (GetCaster() == nullptr) assert(nullptr);
#endif // _DEBUG

		GetOwner()->GetTransform()->SetLocalPos(GetCaster()->GetTransform()->GetLocalPos());
	}
}