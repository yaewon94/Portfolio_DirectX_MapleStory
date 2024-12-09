#include "pch.h"
#include "SkillComponent.h"
#include "AliveObject.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/FlipbookPlayer.h"

SkillComponent::SkillComponent(GameObject* const owner) 
	: Script(owner)
{
	Init();
}

SkillComponent::SkillComponent(const SkillComponent& origin, GameObject* const newOwner) 
	: Script(origin ,newOwner)
{
	Init();
}

SkillComponent::~SkillComponent()
{
}

void SkillComponent::Init()
{
	// 게임오브젝트 비활성화 (스킬 시전할때만 활성화되게)
	GetOwner()->SetActive(false);
}

void SkillComponent::FinalTick()
{
}

void SkillComponent::SetActive(bool flag)
{
	if (flag)
	{
	}
}