#include "pch.h"
#include "Player.h"
#include "SkillComponent.h"
#include "Engine/SharedPtr.h"
#include "Engine/AssetManager.h"
#include "Engine/Texture.h"
#include "Engine/Collider.h"
#include "Engine/KeyManager.h"
#include "Engine/LevelManager.h"

Player::Player(GameObject* const owner) 
	: AliveObject(owner)
	, m_moveSpeed(300.f)
	, m_jumpPower(600.f)
{
	Init();

	// 플레이어 기본 컴포넌트 추가
	// FlipbookPlayer(Render Component)
	m_flipbookPlayer = GetOwner()->AddComponent<FlipbookPlayer>();
	m_flipbookPlayer->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>("Std2D_Material"));
	GetOwner()->GetRenderComponent()->GetMaterial()->GetConstBuffer().fArr[0] = 1.f;
	// idle flipbook
	SharedPtr<Flipbook> flipbook = AssetManager::GetInstance()->AddAsset<Flipbook>("PlayerIdle", "Player\\PlayerIdle.flipbook");
	m_flipbookPlayer->AddFlipbook("Idle", flipbook);
	// move flipbook
	flipbook = AssetManager::GetInstance()->AddAsset<Flipbook>("PlayerMove", "Player\\PlayerMove.flipbook");
	m_flipbookPlayer->AddFlipbook("Move", flipbook);
	// jump flipbook
	flipbook = AssetManager::GetInstance()->AddAsset<Flipbook>("PlayerJump", "Player\\PlayerJump.flipbook");
	m_flipbookPlayer->AddFlipbook("Jump", flipbook);
	m_flipbookPlayer->ChangeFlipbook("Jump");
	// attack flipbook
	flipbook = AssetManager::GetInstance()->AddAsset<Flipbook>("PlayerAttack0", "Player\\PlayerAttack0.flipbook");
	m_flipbookPlayer->AddFlipbook("Attack0", flipbook);
	// rigidbody
	m_rigidbody = GetOwner()->AddComponent<Rigidbody>();
	m_rigidbody->UseGravity(true);
	// collider
	Collider* collider = GetOwner()->AddComponent<Collider>();
	collider->SetScale(Vec2(0.2f, 0.3f));
}

Player::Player(const Player& origin, GameObject* const newOwner) 
	: AliveObject(origin, newOwner)
	, m_moveSpeed(origin.m_moveSpeed)
	, m_jumpPower(origin.m_jumpPower)
{
	Init();

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
	// 플레이어가 사용할 에셋 로드, 관련 필드 초기화
	m_skillMap.insert(make_pair(KEY_LSHIFT, AssetManager::GetInstance()->FindOrAddAsset<AttackSkill>("Skill_ChainLightening", "Skill\\ArchMage_IceLightening\\skills.skill").ptr_dynamic_cast<Skill>()));

	// 인스턴스 공통 필드 초기화
	GetOwner()->GetTransform()->SetLocalScale(Vec3(200.f, 200.f, 1.f));
	GetOwner()->SetTag(OBJECT_TAG::TAG_PLAYER);
	m_jumpStates = 0;
	m_keyStates = 0;

	// KeyManager에 플레이어가 사용할 키값 등록
	KeyManager::GetInstance()->AddKey(KEY_LEFT, this);
	KeyManager::GetInstance()->AddKey(KEY_RIGHT, this);
	KeyManager::GetInstance()->AddKey(KEY_ALT, this);
	KeyManager::GetInstance()->AddKey(KEY_UP, this);
	KeyManager::GetInstance()->AddKey(KEY_LSHIFT, this);

	// 스킬 오브젝트 추가 (자식 오브젝트로 생성 X)
	m_skillComponent = LevelManager::GetInstance()->CreateObject("PlayerSkillObj")->AddComponent<SkillComponent>();
	m_skillComponent->SetCaster(GetOwner());
}