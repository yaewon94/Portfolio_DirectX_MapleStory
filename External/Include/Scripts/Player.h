#pragma once
#include "Engine/Script.h"
#include "Engine/KeyManager.h"
#include "Engine/Transform.h"

// �÷��̾� ������Ʈ
class Player final : public Script, public IKeyEvent
{
	NO_COPY_MOVE(Player)

private:
	enum class MOVE_DIRECTION : int
	{
		LEFT = -1, RIGHT = 1
	};

private:
	float m_moveSpeed;
	float m_moveDelta;
	MOVE_DIRECTION m_moveDir;

public:
	Player(GameObject* const owner);
	Player(const Player& origin, GameObject* const newOwner);
	~Player();

private: // GameObject : Component* �� ���� ȣ��
	virtual void Init() final;
	virtual void Tick() final {}

private: // KeyManager : IKeyEvent* �� ���� ȣ��
	virtual void OnKeyDown(KEY_CODE key) final;
	
private:
	void Move();

public:
	void SetMoveSpeed(float speed)
	{
		m_moveSpeed = speed;
		//m_moveDelta = m_moveSpeed * Transform::UNIT_VEC[DIR_RIGHT].x;
		m_moveDelta = m_moveSpeed * Transform::UNIT_VEC[DIR_RIGHT].x * 0.01f;
	}

private:
	void SetMoveDirection(MOVE_DIRECTION dir)
	{
		if (m_moveDir != dir)
		{
			m_moveDir = dir;
			m_moveDelta *= -1.f;
		}
	}

private:
	virtual Player* Clone(GameObject* const newOwner) final { return new Player(*this, newOwner); }
};