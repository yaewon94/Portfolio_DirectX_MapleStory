#include "pch.h"
#include "SkillComponent.h"
#include "Skill.h"
#include "Engine/GameObject.h"
#include "Engine/FlipbookPlayer.h"

SkillComponent::SkillComponent(GameObject* const owner) 
	: Script(owner)
	, m_caster(nullptr), m_flipbookPlayer(nullptr)
{
}

SkillComponent::SkillComponent(const SkillComponent& origin, GameObject* const newOwner) 
	: Script(origin, newOwner)
	, m_caster(nullptr), m_flipbookPlayer(nullptr)
{
}

SkillComponent::~SkillComponent()
{
}

void SkillComponent::Init()
{
	// 게임오브젝트 비활성화 (스킬 시전할때만 활성화되게)
	GetOwner()->SetActive(false);

	// 컴포넌트 추가
	m_flipbookPlayer = GetOwner()->AddComponent<FlipbookPlayer>();
	m_flipbookPlayer->SetFPS(20);
}
