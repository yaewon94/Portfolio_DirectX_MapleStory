#include "pch.h"
#include "Player.h"

Player::Player(GameObject* const owner) 
	: Script(owner)
{
}

Player::Player(const Player& origin, GameObject* const newOwner) 
	: Script(origin, newOwner)
{
}

Player::~Player()
{
}

void Player::Init()
{
	// KeyManager에 플레이어가 사용할 키값 등록
	KeyManager::GetInstance()->AddKey(KEY_LEFT, this, (KEY_CALLBACK) & Player::Move);
}

void Player::Move(KEY_CODE key)
{
}