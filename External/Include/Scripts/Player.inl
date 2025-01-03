#pragma once
#include "Player.h"
#include "Engine/GameObject.h"
#include "Engine/Rigidbody.h"
#include "Engine/Transform.h"
#include "Engine/FSM.h"
#include "Engine/TimeManager.h"
#include "Engine/CollisionManager.h"
#include "AttackSkill.h"
#include "AttackSkillComponent.h"

inline void Player::OnCollisionEnter(GameObject* other)
{
	if (other->GetTag() & OBJECT_TAG::TAG_GROUND)
	{
		m_jumpStates = CAN_SINGLE_JUMP;
		m_rigidbody->UseGravity(false);
		m_fsm->ChangeState(STATE_TYPE::DEFAULT);
	}
}

inline void Player::OnCollisionTick(GameObject* other)
{
	if (other->GetTag() & OBJECT_TAG::TAG_MONSTER_SKILL)
	{
		if (CollisionManager::GetInstance()->IsPerfectOverlapped(GetOwner(), other))
		{
			other->GetComponent<FSM>()->ChangeState(STATE_TYPE::HIT);
			ChangeHP(other->GetComponent<AttackSkillComponent>()->GetDamage());
		}
	}
}

inline void Player::OnCollisionExit(GameObject* other)
{
	if (m_fsm->GetCurrentState() == STATE_TYPE::DEAD) return;

	if (other->GetTag() & OBJECT_TAG::TAG_GROUND)
	{
		m_jumpStates = 0;
		m_rigidbody->UseGravity(true);
		m_fsm->ChangeState(STATE_TYPE::JUMP);
	}
}

inline void Player::OnKeyTap(KEY_CODE key)
{
	// 공격
	if (key == KEY_LSHIFT)
	{
		m_skillMap.find(key)->second->Execute(this, m_skillObj);
	}
	// 이동
	else if (key == KEY_LEFT || key == KEY_RIGHT)
	{
		if (m_fsm->GetCurrentState() == STATE_TYPE::DEFAULT) m_fsm->ChangeState(STATE_TYPE::MOVE);
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
		m_fsm->ChangeState(STATE_TYPE::DEFAULT);
	}
	else if (key == KEY_ALT)
	{
		if (!m_jumpStates) m_jumpStates = CAN_DOUBLE_JUMP;
	}
	else if (key == KEY_UP)
	{
		m_keyStates &= ~IS_KEYUP_PRESSED;
	}
}

// TODO : MOVE_DIRECTION float타입 할당되게 바꾸기 (enum으로는 안됨)
inline void Player::Move(MOVE_DIRECTION dir)
{
	if (m_moveDir != dir)
	{
		m_moveDir = dir;
		GetOwner()->GetRenderComponent()->GetConstBuffer().direction = (float)m_moveDir;
		m_moveSpeed *= -1.f;
	}
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
		m_fsm->ChangeState(STATE_TYPE::JUMP);
	}
	else if (m_jumpStates & CAN_DOUBLE_JUMP)
	{
		m_jumpStates = IS_DOUBLE_JUMPED;
		if (m_keyStates & IS_KEYUP_PRESSED) m_rigidbody->AddForce(Transform::UNIT_VEC[DIR_UP] * m_jumpPower * 3.f);
		else m_rigidbody->AddForce(Vec3(m_moveDir, 1.f, 0.f) * m_jumpPower);
		m_fsm->ChangeState(STATE_TYPE::JUMP);
	}
}