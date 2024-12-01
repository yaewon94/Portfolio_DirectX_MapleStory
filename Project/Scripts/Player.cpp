#include "pch.h"
#include "Player.h"
#include "Engine/Transform.h"
#include "Engine/MeshRender.h"
#include "Engine/AssetManager.h"
#include "Engine/Mesh.h"
#include "Engine/Rigidbody.h"
#include "Engine/Collider.h"
#include "Engine/TimeManager.h"
#include "Engine/KeyManager.h"

Player::Player(GameObject* const owner) 
	: Script(owner)
	, m_moveSpeed(300.f)
	, m_jumpPower(600.f)
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
	GetOwner()->SetTag(OBJECT_TAG::TAG_PLAYER);
	SetMoveSpeed(m_moveSpeed);
	m_moveDir = MOVE_DIRECTION::RIGHT;
	m_jumpStates = CAN_SINGLE_JUMP;

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

void Player::OnCollisionEnter(GameObject* other)
{
	if (other->GetTag() == OBJECT_TAG::TAG_GROUND)
	{
		m_jumpStates = CAN_SINGLE_JUMP;
		m_rigidbody->UseGravity(false);
	}
}

void Player::OnCollisionExit(GameObject* other)
{
	if (other->GetTag() == OBJECT_TAG::TAG_GROUND)
	{
		m_jumpStates = 0;
		m_rigidbody->UseGravity(true);
	}
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

void Player::OnKeyReleased(KEY_CODE key)
{
	if (key == KEY_ALT)
	{
		if (!m_jumpStates) m_jumpStates = CAN_DOUBLE_JUMP;
	}
}

void Player::Move()
{
	float posX = GetOwner()->GetTransform()->GetLocalPos().x;
	GetOwner()->GetTransform()->SetLocalPosX(posX + m_moveSpeed * DT);
}

void Player::Jump()
{
	if (m_jumpStates & CAN_SINGLE_JUMP)
	{
		m_jumpStates &= ~CAN_SINGLE_JUMP;
		m_rigidbody->UseGravity(true);
		m_rigidbody->AddForce(Transform::UNIT_VEC[DIR_UP] * m_jumpPower);
	}
	else if(m_jumpStates & CAN_DOUBLE_JUMP)
	{
		m_jumpStates = IS_DOUBLE_JUMPED;
		m_rigidbody->AddForce(Vec3(m_moveDir, 1.f, 0.f) * m_jumpPower);
	}
}