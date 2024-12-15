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
	// ���ӿ�����Ʈ ��Ȱ��ȭ (��ų �����Ҷ��� Ȱ��ȭ�ǰ�)
	GetOwner()->SetActive(false);

	// ������Ʈ �߰�
	m_flipbookPlayer = GetOwner()->AddComponent<FlipbookPlayer>();
	m_flipbookPlayer->SetFPS(20);
}
