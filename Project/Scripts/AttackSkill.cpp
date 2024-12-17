#include "pch.h"
#include "AttackSkill.h"
#include "AliveObject.h"
#include "AttackSkillComponent.h"
#include "Engine/GameObject.h"
#include "Engine/FlipbookPlayer.h"
#include "Engine/FSM.h"
#include "Engine/FileManager.h"
#include "Engine/AssetManager.h"

AttackSkill::AttackSkill(const string& Key, const string& relativePath) 
	: Skill(Key, relativePath)
{
}

AttackSkill::~AttackSkill()
{
}

void AttackSkill::Execute(AliveObject* const caster, GameObject* const skillObj)
{
	caster->GetFlipbookPlayer()->ChangeFlipbook(m_casterFlipbookKey);
	caster->GetFlipbookPlayer()->SetRepeat(false);
	caster->GetFSM()->ChangeState(STATE_TYPE::ATTACK);

	skillObj->GetComponent<AttackSkillComponent>()->SetSkill(SharedPtr<AttackSkill>(this));
	skillObj->SetActive(true);
}

int AttackSkill::Load()
{
	if (FAILED(FileManager::GetInstance()->Open(GetFullPathA(), FILE_MODE::READ_TEXT))) return E_FAIL;

	char buff[SIZE_READ_BUFFER];

	if (FAILED(FileManager::GetInstance()->ReadJsonValue("FlipbookPath", buff))) return E_FAIL;
	m_flipbook = AssetManager::GetInstance()->AddAsset<Flipbook>(GetKey(), buff);

	if (FAILED(FileManager::GetInstance()->ReadJsonValue("CasterFlipbookKey", buff))) return E_FAIL;
	m_casterFlipbookKey = buff;

	if (FAILED(FileManager::GetInstance()->ReadJsonValue("MaxDistance", buff))) return E_FAIL;
	m_maxDistance = ToFloat(buff);

	if (FAILED(FileManager::GetInstance()->ReadJsonValue("Velocity_X", buff))) return E_FAIL;
	m_velocity.x = ToFloat(buff);

	if (FAILED(FileManager::GetInstance()->ReadJsonValue("Velocity_Y", buff))) return E_FAIL;
	m_velocity.y = ToFloat(buff);

	if (FAILED(FileManager::GetInstance()->ReadJsonValue("Velocity_Z", buff))) return E_FAIL;
	m_velocity.z = ToFloat(buff);

	FileManager::GetInstance()->Close();

	return S_OK;
}