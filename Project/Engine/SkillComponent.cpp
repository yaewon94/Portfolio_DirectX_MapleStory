#include "pch.h"
#include "SkillComponent.h"
#include "GameObject.h"

SkillComponent::SkillComponent(GameObject* const owner) 
	: Component(owner)
{
	Init();
}

SkillComponent::SkillComponent(const SkillComponent& origin, GameObject* const newOwner) 
	: Component(origin, newOwner)
	, m_skill(origin.m_skill)
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