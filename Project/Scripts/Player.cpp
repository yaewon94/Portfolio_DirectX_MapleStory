#include "pch.h"
#include "Player.h"
#include "Engine/GameObject.h"
#include "Engine/MeshRender.h"
#include "Engine/AssetManager.h"
#include "Engine/Mesh.h"
#include "Engine/Material.h"

Player::Player(GameObject* const owner) 
	: Script(owner)
{
}

Player::Player(const Player& origin, GameObject* const newOwner) 
	: Script(origin, newOwner)
{
}

Player::~Player()
{
}

void Player::Init()
{
	// 플레이어 기본 컴포넌트 추가
	MeshRender* meshRender = GetOwner()->AddComponent<MeshRender>();
	meshRender->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>("RectMesh"));
	meshRender->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>("Std2D_Material"));

	// KeyManager에 플레이어가 사용할 키값 등록
	KeyManager::GetInstance()->AddKey(KEY_LEFT, this, (KEY_CALLBACK) & Player::Move);
}

void Player::Move(KEY_CODE key)
{
}