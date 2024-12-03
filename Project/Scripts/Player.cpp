#include "pch.h"
#include "Player.h"
#include "Engine/AssetManager.h"
#include "Engine/Texture.h"
#include "Engine/Collider.h"
#include "Engine/FlipbookPlayer.h"
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
	GetOwner()->GetTransform()->SetLocalScale(Vec3(200.f, 200.f, 1.f));
	GetOwner()->SetTag(OBJECT_TAG::TAG_PLAYER);
	SetMoveSpeed(m_moveSpeed);
	m_moveDir = MOVE_DIRECTION::RIGHT;
	m_jumpStates = 0;
	m_keyStates = 0;

	// 플레이어 기본 컴포넌트 추가
	// render component
	FlipbookPlayer* flipbookPlayer = GetOwner()->AddComponent<FlipbookPlayer>();
	flipbookPlayer->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>("Std2D_Material"));
	GetOwner()->GetRenderComponent()->GetMaterial()->GetConstBuffer().fArr[0] = 1.f;
	SharedPtr<Flipbook> flipbook = AssetManager::GetInstance()->AddAsset<Flipbook>("PlayerIdle", "");
	flipbook->SetAtlasTexture(AssetManager::GetInstance()->AddAsset<Texture>("PlayerIdle", "Player\\PlayerIdleFlipbook.png"), 1, 3, GetOwner());
	flipbookPlayer->AddFlipbook("Idle", flipbook);
	// rigidbody
	m_rigidbody = GetOwner()->AddComponent<Rigidbody>();
	m_rigidbody->UseGravity(true);
	// collider
	Collider* collider = GetOwner()->AddComponent<Collider>();
	collider->SetScale(Vec2(0.2f, 0.3f));
	collider->SetOffset(Vec2(-0.1f, 0.1f));

	// KeyManager에 플레이어가 사용할 키값 등록
	KeyManager::GetInstance()->AddKey(KEY_LEFT, this);
	KeyManager::GetInstance()->AddKey(KEY_RIGHT, this);
	KeyManager::GetInstance()->AddKey(KEY_ALT, this);
	KeyManager::GetInstance()->AddKey(KEY_UP, this);
}