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
	// 인스턴스 공통 필드 초기화
	GetOwner()->SetTag(OBJECT_TAG::PLAYER);
	SetMoveSpeed(m_moveSpeed);
	m_moveDir = MOVE_DIRECTION::RIGHT;
	m_canJump = true;

	// 플레이어 기본 컴포넌트 추가
	// render component
	MeshRender* meshRender = GetOwner()->AddComponent<MeshRender>();
	meshRender->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>("RectMesh"));
	meshRender->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>("Std2D_Material"));
	GetOwner()->GetRenderComponent()->GetMaterial()->GetConstBuffer().fArr[0] = 1.f;
	// rigidbody
	m_rigidbody = GetOwner()->AddComponent<Rigidbody>();
	// collider
	GetOwner()->AddComponent<Collider>();

	// KeyManager에 플레이어가 사용할 키값 등록
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
	// 누르면 윈도우 메세지 루프 걸리는듯 Engine::Progress()가 멈춰버림
	// 윈도우 프로시저에서 VK_MENU 처리 막음
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