#include "pch.h"
#include "TestLevel.h"
#include "Engine/LevelManager.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Scripts/Player.h"
#include "Scripts/Ground.h"

void CreateTestLevel()
{
	GameObject* obj = LevelManager::GetInstance()->CreateObject("Player");
	obj->AddComponent<Player>();
	obj->Init();

	obj = LevelManager::GetInstance()->CreateObject("Ground");
	obj->GetTransform()->SetLocalPosY(-100.f);
	obj->GetTransform()->SetLocalScaleX(500.f);
	obj->AddComponent<Ground>();
	obj->Init();
}