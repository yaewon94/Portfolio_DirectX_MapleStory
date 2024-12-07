#pragma once
#include "Engine/Script.h"
#include "Engine/IKeyEvent.h"

// 플레이어 컴포넌트
class Player final : public Script, public IKeyEvent
{
	NO_COPY_MOVE(Player)

private:
	// 이동 방향
	enum MOVE_DIRECTION : int
	{
		LEFT = -1, RIGHT = 1
	};

	// 점프 관련 상태값
	enum JUMP_STATE : byte
	{
		CAN_SINGLE_JUMP = 1,
		IS_DOUBLE_JUMPED = CAN_SINGLE_JUMP << 1,
		CAN_DOUBLE_JUMP = IS_DOUBLE_JUMPED << 1,
		//IS_KEYUP_PRESSED = CAN_DOUBLE_JUMP << 1
	};
	typedef byte JUMP_STATES;

	// KEY 관련 상태값
	enum PLAYER_KEY_STATE : byte
	{
		IS_KEYUP_PRESSED = 1 // 윗점프 뿐만 아니라 포탈이동 등에도 쓰일 수 있으므로 JUMP_STATE 과는 별개의 타입으로 선언함
	};
	typedef byte PLAYER_KEY_STATES;

private:
	class FlipbookPlayer* m_flipbookPlayer;

	float m_moveSpeed; // 왼쪽으로 방향 전환 시 -값으로 바뀜
	MOVE_DIRECTION m_moveDir;

	class Rigidbody* m_rigidbody;
	float m_jumpPower;
	JUMP_STATES m_jumpStates;
	PLAYER_KEY_STATES m_keyStates;
	
public:
	Player(GameObject* const owner);
	Player(const Player& origin, GameObject* const newOwner);
	~Player();

private: // GameObject : Component* 를 통해 호출
	virtual void Init() final;

	virtual void OnCollisionEnter(GameObject* other) final;
	virtual void OnCollisionExit(GameObject* other) final;

private: // KeyManager : IKeyEvent* 를 통해 호출
	virtual void OnKeyTap(KEY_CODE key) final;
	virtual void OnKeyDown(KEY_CODE key) final;
	virtual void OnKeyReleased(KEY_CODE key) final;
	
private:
	void Move(MOVE_DIRECTION dir);
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
	virtual Player* Clone(GameObject* const newOwner) final { return new Player(*this, newOwner); }
};

#include "Player.inl"