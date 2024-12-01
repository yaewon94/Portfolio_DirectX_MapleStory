#pragma once
#include "Player.h"
#include "Engine/GameObject.h"
#include "Engine/Rigidbody.h"
#include "Engine/Transform.h"
#include "Engine/TimeManager.h"

inline void Player::OnCollisionEnter(GameObject* other)
{
	if (other->GetTag() == OBJECT_TAG::TAG_GROUND)
	{
		m_jumpStates = CAN_SINGLE_JUMP;
		m_rigidbody->UseGravity(false);
	}
}

inline void Player::OnCollisionExit(GameObject* other)
{
	if (other->GetTag() == OBJECT_TAG::TAG_GROUND)
	{
		m_jumpStates = 0;
		m_rigidbody->UseGravity(true);
	}
}

inline void Player::OnKeyDown(KEY_CODE key)
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

inline void Player::OnKeyReleased(KEY_CODE key)
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

inline void Player::Move()
{
	float posX = GetOwner()->GetTransform()->GetLocalPos().x;
	GetOwner()->GetTransform()->SetLocalPosX(posX + m_moveSpeed * DT);
}

inline void Player::Jump()
{
	if (m_jumpStates & CAN_SINGLE_JUMP)
	{
		m_jumpStates &= ~CAN_SINGLE_JUMP;
		m_rigidbody->UseGravity(true);
		m_rigidbody->AddForce(Transform::UNIT_VEC[DIR_UP] * m_jumpPower);
	}
	else if (m_jumpStates & CAN_DOUBLE_JUMP)
	{
		m_jumpStates = IS_DOUBLE_JUMPED;
		if (m_keyStates & IS_KEYUP_PRESSED) m_rigidbody->AddForce(Transform::UNIT_VEC[DIR_UP] * m_jumpPower * 3.f);
		else m_rigidbody->AddForce(Vec3(m_moveDir, 1.f, 0.f) * m_jumpPower);
	}
}

inline void Player::SetMoveDirection(MOVE_DIRECTION dir)
{
	if (m_moveDir != dir)
	{
		m_moveDir = dir;
		m_moveSpeed *= -1.f;
		GetOwner()->GetRenderComponent()->GetMaterial()->GetConstBuffer().fArr[0] *= -1.f;
	}
}