#include "pch.h"
#include "Player.h"
#include "Engine/KeyManager.h"
#include "Engine/LevelManager.h"
#include "Engine/SharedPtr.h"
#include "Engine/AssetManager.h"
#include "Engine/Texture.h"
#include "PlayerDefaultState.h"
#include "PlayerMoveState.h"
#include "PlayerJumpState.h"
#include "PlayerAttackState.h"
#include "Engine/Collider.h"
#include "Engine/FlipbookPlayer.h"
#include "AttackSkillComponent.h"

Player::Player(GameObject* const owner) 
	: AliveObject(owner)
	, m_jumpPower(600.f)
{
	// 컴포넌트 추가
	m_flipbookPlayer = GetOwner()->AddComponent<FlipbookPlayer>();
	SharedPtr<Flipbook> flipbook = AssetManager::GetInstance()->AddAsset<Flipbook>("PlayerIdle", "Player\\PlayerIdle.flipbook");
	m_flipbookPlayer->AddFlipbook("Idle", flipbook);
	flipbook = AssetManager::GetInstance()->AddAsset<Flipbook>("PlayerMove", "Player\\PlayerMove.flipbook");
	m_flipbookPlayer->AddFlipbook("Move", flipbook);
	flipbook = AssetManager::GetInstance()->AddAsset<Flipbook>("PlayerJump", "Player\\PlayerJump.flipbook");
	m_flipbookPlayer->AddFlipbook("Jump", flipbook);
	flipbook = AssetManager::GetInstance()->AddAsset<Flipbook>("PlayerAttack0", "Player\\PlayerAttack0.flipbook");
	m_flipbookPlayer->AddFlipbook("Attack0", flipbook);
	GetOwner()->AddComponent<Rigidbody>();
	GetOwner()->AddComponent<Collider>()->SetScale(Vec2(0.2f, 0.3f));
	m_fsm = GetOwner()->AddComponent<FSM>();
	m_fsm->AddState<PlayerDefaultState>(STATE_TYPE::DEFAULT);
	m_fsm->AddState<PlayerMoveState>(STATE_TYPE::MOVE);
	m_fsm->AddState<PlayerJumpState>(STATE_TYPE::JUMP);
	m_fsm->AddState<PlayerAttackState>(STATE_TYPE::ATTACK);

	// 에셋 추가
	m_skillMap.insert(make_pair(KEY_LSHIFT, AssetManager::GetInstance()->FindOrAddAsset<AttackSkill>("Skill_ChainLightening", "Job\\ArchMage_IceLightening\\Skill\\skills.skill").ptr_dynamic_cast<Skill>()));

	// KeyManager에 플레이어가 사용할 키값 등록
	KeyManager::GetInstance()->AddKey(KEY_LEFT, this);
	KeyManager::GetInstance()->AddKey(KEY_RIGHT, this);
	KeyManager::GetInstance()->AddKey(KEY_ALT, this);
	KeyManager::GetInstance()->AddKey(KEY_UP, this);
	KeyManager::GetInstance()->AddKey(KEY_LSHIFT, this);
}

Player::Player(const Player& origin, GameObject* const newOwner) 
	: AliveObject(origin, newOwner)
	, m_jumpPower(origin.m_jumpPower)
{
	// 같은 스킬에셋 공유
	for (const auto& pair : origin.m_skillMap)
	{
		m_skillMap.insert(make_pair(pair.first, pair.second));
	}
}

Player::~Player()
{
}

void Player::Init()
{
	AliveObject::Init();

	// 인스턴스 공통 필드 초기화
	m_rigidbody = GetOwner()->GetComponent<Rigidbody>();
	m_rigidbody->UseGravity(true);
	GetOwner()->GetTransform()->SetLocalScale(Vec3(200.f, 200.f, 1.f));
	GetOwner()->SetTag(OBJECT_TAG::TAG_PLAYER);
	m_jumpStates = 0;
	m_keyStates = 0;

	// 스킬 오브젝트 추가 (자식 오브젝트로 생성 X)
	m_skillObj = LevelManager::GetInstance()->CreateObject("PlayerSkillObj");
	m_skillObj->SetTag(OBJECT_TAG::TAG_PLAYER_SKILL);
	m_skillObj->GetTransform()->SetLocalScale(Vec3(200.f, 200.f, 1.f));
	m_skillObj->AddComponent<AttackSkillComponent>()->SetCaster(this);
	m_skillObj->Init();
}