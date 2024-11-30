#include "pch.h"
#include "Player.h"
#include "Engine/Transform.h"
#include "Engine/MeshRender.h"
#include "Engine/AssetManager.h"
#include "Engine/Mesh.h"
#include "Engine/Rigidbody.h"
#include "Engine/Collider.h"
#include "Engine/TimeManager.h"

Player::Player(GameObject* const owner) 
	: Script(owner)
	, m_moveSpeed(300.f)
	, m_jumpPower(500.f)
{
	Init();
}

Player::Player(const Player& origin, GameObject* const newOwner) 
	: Script(origin, newOwner)
	, m_moveSpeed(origin.m_moveSpeed)
	, m_jumpPower(origin.m_jumpPower)
{
	Init();
}

Player::~Player()
{
}

void Player::Init()
{
	// �ν��Ͻ� ���� �ʵ� �ʱ�ȭ
	GetOwner()->SetTag(OBJECT_TAG::PLAYER);
	SetMoveSpeed(m_moveSpeed);
	m_moveDir = MOVE_DIRECTION::RIGHT;
	m_canJump = true;

	// �÷��̾� �⺻ ������Ʈ �߰�
	// render component
	MeshRender* meshRender = GetOwner()->AddComponent<MeshRender>();
	meshRender->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>("RectMesh"));
	meshRender->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>("Std2D_Material"));
	GetOwner()->GetRenderComponent()->GetMaterial()->GetConstBuffer().fArr[0] = 1.f;
	// rigidbody
	m_rigidbody = GetOwner()->AddComponent<Rigidbody>();
	// collider
	GetOwner()->AddComponent<Collider>();

	// KeyManager�� �÷��̾ ����� Ű�� ���
	KeyManager::GetInstance()->AddKey(KEY_LEFT, this);
	KeyManager::GetInstance()->AddKey(KEY_RIGHT, this);
	KeyManager::GetInstance()->AddKey(KEY_ALT, this);
}

void Player::OnKeyDown(KEY_CODE key)
{
	if (key == KEY_LEFT)
	{
		SetMoveDirection(MOVE_DIRECTION::LEFT);
		Move();
	}
	else if (key == KEY_RIGHT)
	{
		SetMoveDirection(MOVE_DIRECTION::RIGHT);
		Move();
	}
	// ������ ������ �޼��� ���� �ɸ��µ� Engine::Progress()�� �������
	// ������ ���ν������� VK_MENU ó�� ����
	else if (key == KEY_ALT)
	{
		Jump();
	}
}

void Player::Move()
{
	float posX = GetOwner()->GetTransform()->GetLocalPos().x;
	GetOwner()->GetTransform()->SetLocalPosX(posX + m_moveSpeed * DT);
}

void Player::Jump()
{
	if (m_canJump)
	{
		m_canJump = false;
		m_rigidbody->UseGravity(true);
		m_rigidbody->AddForce(Transform::UNIT_VEC[DIR_UP] * m_jumpPower);
	}
}