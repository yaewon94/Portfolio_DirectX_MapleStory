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
	// ���ӿ�����Ʈ ��Ȱ��ȭ (��ų �����Ҷ��� Ȱ��ȭ�ǰ�)
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