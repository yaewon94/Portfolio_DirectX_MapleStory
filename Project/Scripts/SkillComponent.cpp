#include "pch.h"
#include "SkillComponent.h"
#include "Engine/GameObject.h"

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
	GetOwner()->SetActive(false);
}

void SkillComponent::FinalTick()
{
}