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
	// �÷��̾� �⺻ ������Ʈ �߰�
	MeshRender* meshRender = GetOwner()->AddComponent<MeshRender>();
	meshRender->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>("RectMesh"));
	meshRender->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>("Std2D_Material"));

	// KeyManager�� �÷��̾ ����� Ű�� ���
	KeyManager::GetInstance()->AddKey(KEY_LEFT, this, (KEY_CALLBACK) & Player::Move);
}

void Player::Move(KEY_CODE key)
{
}