#pragma once
#include "Engine/Script.h"
#include "Engine/KeyManager.h"

// 플레이어 컴포넌트
class Player final : public Script, public IKeyEvent
{
	NO_COPY_MOVE(Player)

private:
	enum class MOVE_DIRECTION : int
	{
		LEFT = -1, RIGHT = 1
	};

private:
	float m_moveSpeed; // 왼쪽으로 방향 전환 시 -값으로 바뀜
	MOVE_DIRECTION m_moveDir;

	class Rigidbody* m_rigidbody;
	float m_jumpPower;
	bool m_canJump;

public:
	Player(GameObject* const owner);
	Player(const Player& origin, GameObject* const newOwner);
	~Player();

private: // GameObject : Component* 를 통해 호출
	virtual void Init() final;

	virtual void OnCollisionEnter(GameObject* other) final;
	virtual void OnCollisionExit(GameObject* other) final;

private: // KeyManager : IKeyEvent* 를 통해 호출
	virtual void OnKeyDown(KEY_CODE key) final;
	
private:
	void Move();
	void Jump();

public:
	float GetMoveSpeed() const
	{ 
		if (m_moveSpeed < 0.f) return m_moveSpeed * -1.f;
		else return m_moveSpeed;
	}
	void SetMoveSpeed(float speed) { m_moveSpeed = speed; }

	float GetJumpPower() const { return m_jumpPower; }
	void SetJumpPower(float jumpPower)
	{
		if (jumpPower <= 0.f)
		{
			MessageBox(nullptr, L"점프력은 양수값만 가능합니다", L"ERROR", MB_OK);
			return;
		}
		m_jumpPower = jumpPower;
	}

private:
	void SetMoveDirection(MOVE_DIRECTION dir);

private:
	virtual Player* Clone(GameObject* const newOwner) final { return new Player(*this, newOwner); }
};

#include "Player.inl"