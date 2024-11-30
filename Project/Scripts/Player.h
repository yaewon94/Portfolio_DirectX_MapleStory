#pragma once
#include "Engine/Script.h"
#include "Engine/KeyManager.h"

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
	float m_moveSpeed; // �������� ���� ��ȯ �� -������ �ٲ�
	MOVE_DIRECTION m_moveDir;

	class Rigidbody* m_rigidbody;
	float m_jumpPower;
	bool m_canJump;

public:
	Player(GameObject* const owner);
	Player(const Player& origin, GameObject* const newOwner);
	~Player();

private: // GameObject : Component* �� ���� ȣ��
	virtual void Init() final;

	virtual void OnCollisionEnter(GameObject* other) final;
	virtual void OnCollisionExit(GameObject* other) final;

private: // KeyManager : IKeyEvent* �� ���� ȣ��
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
			MessageBox(nullptr, L"�������� ������� �����մϴ�", L"ERROR", MB_OK);
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