#include "pch.h"
#include "AttackSkill.h"
#include "AliveObject.h"
#include "SkillComponent.h"
#include "Engine/GameObject.h"
#include "Engine/FlipbookPlayer.h"
#include "Engine/FileManager.h"
#include "Engine/AssetManager.h"

AttackSkill::AttackSkill(const string& Key, const string& relativePath) 
	: Skill(Key, relativePath)
{
}

AttackSkill::~AttackSkill()
{
}

void AttackSkill::Execute(AliveObject* const caster, SkillComponent* const skillComponent)
{
#ifdef _DEBUG
	if (caster == nullptr || skillComponent == nullptr) assert(nullptr);
#endif // _DEBUG

	caster->GetFlipbookPlayer()->ChangeFlipbook(m_casterFlipbookKey);
	skillComponent->SetSkill(SharedPtr<Skill>(this));
	skillComponent->GetOwner()->SetActive(true);
}

int AttackSkill::Load()
{
	if (FAILED(FileManager::GetInstance()->Open(GetFullPathA(), FILE_MODE::READ_TEXT))) return E_FAIL;

	char buff[SIZE_READ_BUFFER];

	if (FAILED(FileManager::GetInstance()->ReadJsonValue("FlipbookPath", buff))) return E_FAIL;
	m_flipbook = AssetManager::GetInstance()->AddAsset<Flipbook>(GetKey(), buff);

	if (FAILED(FileManager::GetInstance()->ReadJsonValue("CasterFlipbookKey", buff))) return E_FAIL;
	m_casterFlipbookKey = buff;

	FileManager::GetInstance()->Close();

	return S_OK;
}