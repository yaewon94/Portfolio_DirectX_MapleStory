#include "pch.h"
#include "Player.h"
#include "Engine/MeshRender.h"
#include "Engine/AssetManager.h"
#include "Engine/Mesh.h"
#include "Engine/Collider.h"
#include "Engine/KeyManager.h"
#include "Engine/FSM.h"
#include "PlayerDefaultState.h"

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
	// fsm
	FSM* fsm = GetOwner()->AddComponent<FSM>();
	fsm->AddState<PlayerDefaultState>(STATE_TYPE::DEFAULT);
	fsm->ChangeState(STATE_TYPE::DEFAULT);

	// KeyManager에 플레이어가 사용할 키값 등록
	KeyManager::GetInstance()->AddKey(KEY_LEFT, this);
	KeyManager::GetInstance()->AddKey(KEY_RIGHT, this);
	KeyManager::GetInstance()->AddKey(KEY_ALT, this);
	KeyManager::GetInstance()->AddKey(KEY_UP, this);
}