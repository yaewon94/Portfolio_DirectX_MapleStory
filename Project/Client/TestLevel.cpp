#include "pch.h"
#include "TestLevel.h"
#include "Engine/LevelManager.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/FlipbookPlayer.h"
#include "Engine/AssetManager.h"
#include "Scripts/Player.h"
#include "Scripts/Ground.h"
#include "Scripts/Monster.h"
#include "Scripts/AttackSkill.h"

void CreateTestLevel()
{
	GameObject* obj = LevelManager::GetInstance()->CreateObject("Player");
	obj->AddComponent<Player>();
	obj->Init();

	obj = LevelManager::GetInstance()->CreateObject("Ground");
	obj->GetTransform()->SetLocalPosY(-150.f);
	obj->GetTransform()->SetLocalScaleX(800.f);
	obj->AddComponent<Ground>();
	obj->Init();

	obj = LevelManager::GetInstance()->CreateObject("Lucid");
	obj->GetTransform()->SetLocalPosX(300.f);
	obj->GetTransform()->SetLocalScale(Vec3(250.f, 250.f, 1.f));
	Monster* monster = obj->AddComponent<Monster>();
	monster->SetMoveDirection(IMovable::MOVE_DIRECTION::LEFT);
	monster->AddSkill(AssetManager::GetInstance()->AddAsset<AttackSkill>("Skill_FairyDust", "Monster\\Lucid\\skills.skill").ptr_dynamic_cast<Skill>());
	FlipbookPlayer* flipbookPlayer = monster->GetFlipbookPlayer();
	flipbookPlayer->AddFlipbook("Idle", AssetManager::GetInstance()->AddAsset<Flipbook>("1phaseIdle", "Monster\\Lucid\\1phaseIdle.flipbook"));
	flipbookPlayer->AddFlipbook("Dead", AssetManager::GetInstance()->AddAsset<Flipbook>("1phaseDead", "Monster\\Lucid\\1phaseDead.flipbook"));
	flipbookPlayer->AddFlipbook("Attack0", AssetManager::GetInstance()->AddAsset<Flipbook>("1phaseAttack0", "Monster\\Lucid\\1phaseAttack0.flipbook"));
	obj->Init();
}