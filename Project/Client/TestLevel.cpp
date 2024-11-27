#include "pch.h"
#include "TestLevel.h"
#include "Engine/LevelManager.h"
#include "Engine/GameObject.h"
#include "Scripts/Player.h"

void CreateTestLevel()
{
	GameObject* obj = LevelManager::GetInstance()->CreateObject("Player");
	obj->AddComponent<Player>();
	obj->Init();
}