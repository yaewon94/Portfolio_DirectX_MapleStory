#include "pch.h"
#include "Player.h"
#include "Engine/GameObject.h"
#include "Engine/MeshRender.h"
#include "Engine/AssetManager.h"
#include "Engine/Mesh.h"
#include "Engine/Material.h"
//#include "Engine/TimeManager.h"

Player::Player(GameObject* const owner) 
	: Script(owner)
	, m_moveSpeed(500.f)
{
}

Player::Player(const Player& origin, GameObject* const newOwner) 
	: Script(origin, newOwner)
	, m_moveSpeed(origin.m_moveSpeed)
{
}

Player::~Player()
{
}

void Player::Init()
{
	// �ν��Ͻ� ���� �ʵ� �ʱ�ȭ
	SetMoveSpeed(m_moveSpeed);
	m_moveDir = MOVE_DIRECTION::RIGHT;
	SetMoveDirection(MOVE_DIRECTION::LEFT);

	// �÷��̾� �⺻ ������Ʈ �߰�
	MeshRender* meshRender = GetOwner()->AddComponent<MeshRender>();
	meshRender->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>("RectMesh"));
	meshRender->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>("Std2D_Material"));

	// KeyManager�� �÷��̾ ����� Ű�� ���
	KeyManager::GetInstance()->AddKey(KEY_LEFT, this, (KEY_CALLBACK)&Player::OnKeyDown);
	KeyManager::GetInstance()->AddKey(KEY_RIGHT, this, (KEY_CALLBACK)&Player::OnKeyDown);
}

void Player::OnKeyDown(KEY_CODE key)
{
	if (key == KEY_LEFT)
	{
		SetMoveDirection(MOVE_DIRECTION::LEFT);
		GetOwner()->GetRenderComponent()->GetMaterial()->GetConstBuffer().fArr[0] = -1.f;
		Move();
	}
	else if (key == KEY_RIGHT)
	{
		SetMoveDirection(MOVE_DIRECTION::RIGHT);
		GetOwner()->GetRenderComponent()->GetMaterial()->GetConstBuffer().fArr[0] = 1.f;
		Move();
	}
}

void Player::Move()
{
	GetOwner()->GetTransform()->SetLocalPosX(GetOwner()->GetTransform()->GetLocalPos().x + m_moveDelta);
	//GetOwner()->GetTransform()->SetLocalPosX(GetOwner()->GetTransform()->GetLocalPos().x + m_moveDelta * DT);
}