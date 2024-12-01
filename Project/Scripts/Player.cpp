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
	// 인스턴스 공통 필드 초기화
	GetOwner()->SetTag(OBJECT_TAG::TAG_PLAYER);
	SetMoveSpeed(m_moveSpeed);
	m_moveDir = MOVE_DIRECTION::RIGHT;
	m_jumpStates = CAN_SINGLE_JUMP;
	m_keyStates = 0;

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
	KeyManager::GetInstance()->AddKey(KEY_UP, this);
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
	switch (key)
	{
	case KEY_LEFT:
		SetMoveDirection(MOVE_DIRECTION::LEFT);
		Move();
		break;
	case KEY_RIGHT:
		SetMoveDirection(MOVE_DIRECTION::RIGHT);
		Move();
		break;
	// 누르면 윈도우 메세지 루프 걸리는듯 Engine::Progress()가 멈춰버림 => 윈도우 프로시저에서 VK_MENU 처리 막는 코드 추가했음
	case KEY_ALT:
		Jump();
		break;
	case KEY_UP:
		m_keyStates |= IS_KEYUP_PRESSED;
		break;
	default:
#ifdef _DEBUG
		assert(nullptr);
#endif // _DEBUG
	}
}

void Player::OnKeyReleased(KEY_CODE key)
{
	if (key == KEY_ALT)
	{
		if (!m_jumpStates) m_jumpStates = CAN_DOUBLE_JUMP;
	}
	else if (key == KEY_UP)
	{
		m_keyStates ^= ~IS_KEYUP_PRESSED; // TODO : 오류나는지 체크
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
		if (m_keyStates & IS_KEYUP_PRESSED) m_rigidbody->AddForce(Transform::UNIT_VEC[DIR_UP] * m_jumpPower * 3.f);
		else m_rigidbody->AddForce(Vec3(m_moveDir, 1.f, 0.f) * m_jumpPower);
	}
}