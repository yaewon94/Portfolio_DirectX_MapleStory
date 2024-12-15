#pragma once
#include "Player.h"
#include "Engine/GameObject.h"
#include "Engine/Rigidbody.h"
#include "Engine/Transform.h"
#include "Engine/FlipbookPlayer.h"
#include "Engine/TimeManager.h"
#include "AttackSkill.h"

inline void Player::OnCollisionEnter(GameObject* other)
{
	if (other->GetTag() == OBJECT_TAG::TAG_GROUND)
	{
		m_jumpStates = CAN_SINGLE_JUMP;
		m_rigidbody->UseGravity(false);
		m_flipbookPlayer->ChangeFlipbook("Idle");
	}
}

inline void Player::OnCollisionExit(GameObject* other)
{
	if (other->GetTag() == OBJECT_TAG::TAG_GROUND)
	{
		m_jumpStates = 0;
		m_rigidbody->UseGravity(true);
		m_flipbookPlayer->ChangeFlipbook("Jump");
	}
}

inline void Player::OnKeyTap(KEY_CODE key)
{
	// 공격
	if (key == KEY_LSHIFT)
	{
		m_skillMap.find(key)->second->Execute(this, m_skillComponent);
	}
	// 이동
	else if (key == KEY_LEFT || key == KEY_RIGHT)
	{
		if (m_flipbookPlayer->GetCurrentFlipbookName() == "Idle") m_flipbookPlayer->ChangeFlipbook("Move");
	}
}

inline void Player::OnKeyDown(KEY_CODE key)
{
	switch (key)
	{
	case KEY_LEFT:
		Move(MOVE_DIRECTION::LEFT);
		break;
	case KEY_RIGHT:
		Move(MOVE_DIRECTION::RIGHT);
		break;
		// 누르면 윈도우 메세지 루프 걸리는듯 Engine::Progress()가 멈춰버림 => 윈도우 프로시저에서 VK_MENU 처리 막는 코드 추가했음
	case KEY_ALT:
		Jump();
		break;
	case KEY_UP:
		m_keyStates |= IS_KEYUP_PRESSED;
		break;
	}
}

inline void Player::OnKeyReleased(KEY_CODE key)
{
	if (key == KEY_LEFT || key == KEY_RIGHT)
	{
		m_flipbookPlayer->ChangeFlipbook("Idle");
	}
	else if (key == KEY_ALT)
	{
		if (!m_jumpStates) m_jumpStates = CAN_DOUBLE_JUMP;
	}
	else if (key == KEY_UP)
	{
		m_keyStates ^= IS_KEYUP_PRESSED; // TODO : 오류나는지 체크
	}
}

// TODO : MOVE_DIRECTION float타입 할당되게 바꾸기 (enum으로는 안됨)
inline void Player::Move(MOVE_DIRECTION dir)
{
	m_moveDir = dir;
	GetOwner()->GetRenderComponent()->GetMaterial()->GetConstBuffer().fArr[0] = m_moveDir;
	float posX = GetOwner()->GetTransform()->GetLocalPos().x;
	GetOwner()->GetTransform()->SetLocalPosX(posX + m_moveSpeed * DT * m_moveDir);
}

inline void Player::Jump()
{
	if (m_jumpStates & CAN_SINGLE_JUMP)
	{
		m_jumpStates &= ~CAN_SINGLE_JUMP;
		m_rigidbody->UseGravity(true);
		m_rigidbody->AddForce(Transform::UNIT_VEC[DIR_UP] * m_jumpPower);
		m_flipbookPlayer->ChangeFlipbook("Jump");
	}
	else if (m_jumpStates & CAN_DOUBLE_JUMP)
	{
		m_jumpStates = IS_DOUBLE_JUMPED;
		if (m_keyStates & IS_KEYUP_PRESSED) m_rigidbody->AddForce(Transform::UNIT_VEC[DIR_UP] * m_jumpPower * 3.f);
		else m_rigidbody->AddForce(Vec3(m_moveDir, 1.f, 0.f) * m_jumpPower);
		m_flipbookPlayer->ChangeFlipbook("Jump");
	}
}