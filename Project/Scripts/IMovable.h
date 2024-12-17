#pragma once
#include "pch.h"

class IMovable
{
	NO_COPY_MOVE(IMovable)

protected:
	// �̵� ����
	enum MOVE_DIRECTION : int
	{
		LEFT = -1, RIGHT = 1
	};

protected:
	float m_moveSpeed;
	MOVE_DIRECTION m_moveDir;

protected:
	IMovable() 
		: m_moveDir(MOVE_DIRECTION::RIGHT), m_moveSpeed(300.f) {}
	IMovable(float moveSpeed) 
		: m_moveDir(MOVE_DIRECTION::RIGHT), m_moveSpeed(moveSpeed) {}
	virtual ~IMovable() {}

protected:
	inline virtual void Move(MOVE_DIRECTION dir) = 0;

public:
	float GetMoveSpeed() const { return m_moveSpeed; }
	void SetMoveSpeed(float speed) { m_moveSpeed = speed; }
};