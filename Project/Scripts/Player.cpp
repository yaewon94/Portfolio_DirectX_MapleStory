#include "pch.h"
#include "Player.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/MeshRender.h"
#include "Engine/AssetManager.h"
#include "Engine/Mesh.h"
#include "Engine/Material.h"
//#include "Engine/TimeManager.h"

Player::Player(GameObject* const owner) 
	: Script(owner)
	, m_moveSpeed(150.f)
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

	// �÷��̾� �⺻ ������Ʈ �߰�
	MeshRender* meshRender = GetOwner()->AddComponent<MeshRender>();
	meshRender->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>("RectMesh"));
	meshRender->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>("Std2D_Material"));
	GetOwner()->GetRenderComponent()->GetMaterial()->GetConstBuffer().fArr[0] = 1.f;

	// KeyManager�� �÷��̾ ����� Ű�� ���
	KeyManager::GetInstance()->AddKey(KEY_LEFT, this);
	KeyManager::GetInstance()->AddKey(KEY_RIGHT, this);
	//KeyManager::GetInstance()->AddKey(KEY_ALT, this);
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
	/*else if (key == KEY_ALT)
	{
		Jump();
	}*/
}

void Player::Move()
{
	GetOwner()->GetTransform()->SetLocalPosX(GetOwner()->GetTransform()->GetLocalPos().x + m_moveDelta);
	//GetOwner()->GetTransform()->SetLocalPosX(GetOwner()->GetTransform()->GetLocalPos().x + m_moveDelta * DT);
}

//void Player::Jump()
//{
//}

void Player::SetMoveSpeed(float speed)
{
	m_moveSpeed = speed;
	//m_moveDelta = m_moveSpeed * Transform::UNIT_VEC[DIR_RIGHT].x;
	// ERROR : m_moveDelta ���� �Ҽ��� �Ʒ��ڸ��� �ִ� ��� ���ʹ��� ��ȯ �� �̹��� �Ϻ� �ְ�
	m_moveDelta = m_moveSpeed * Transform::UNIT_VEC[DIR_RIGHT].x * 0.01f;
}

void Player::SetMoveDirection(MOVE_DIRECTION dir)
{
	if (m_moveDir != dir)
	{
		m_moveDir = dir;
		m_moveDelta *= -1.f;
		GetOwner()->GetRenderComponent()->GetMaterial()->GetConstBuffer().fArr[0] *= -1.f;
	}
}