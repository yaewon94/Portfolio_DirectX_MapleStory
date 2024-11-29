#pragma once
#include "Player.h"
#include "Engine/GameObject.h"

inline void Player::SetMoveDirection(MOVE_DIRECTION dir)
{
	if (m_moveDir != dir)
	{
		m_moveDir = dir;
		m_moveSpeed *= -1.f;
		GetOwner()->GetRenderComponent()->GetMaterial()->GetConstBuffer().fArr[0] *= -1.f;
	}
}