#pragma once
#include "Engine/Script.h"
#include "IMovable.h"

typedef UINT HP;
typedef HP Power;

// �÷��̾�, ���� �� ���¸� ������ �ְ�, �̵�����, ��ų��밡�� ���� Ư¡�� ���� ������Ʈ
class AliveObject : public Script, public IMovable
{
	NO_COPY_MOVE(AliveObject)

private:
	HP m_maxHP, m_curHP;
	Power m_power;

protected:
	class FlipbookPlayer* m_flipbookPlayer;
	class FSM* m_fsm;
	GameObject* m_skillObj;

protected:
	AliveObject(GameObject* const owner);
	AliveObject(const AliveObject& origin, GameObject* const newOwner);
	~AliveObject();

protected: // GameObject : Component* �� ���� ȣ��
	virtual void Init() override;

public:
	FSM* const GetFSM() const { return m_fsm; }
	FlipbookPlayer* const GetFlipbookPlayer() const { return m_flipbookPlayer; }
	GameObject* const GetSkillObject() const { return m_skillObj; }
	Power GetPower() const { return m_power; }

protected:
	void ChangeHP(HP changeAmount);
};

////////////////////////////////////////////////////
// AliveObject.inl
////////////////////////////////////////////////////
#include "Engine/FSM.h"
inline void AliveObject::ChangeHP(HP changeAmount)
{
	// ���� ü�¿� �ݿ�
	// TODO : HP Ÿ���� signed �� �ٲ� ��� overflow, underflow ����üũ�ڵ� �ٲ�� ��
	if (m_curHP + changeAmount < m_curHP) // overflow
	{
		m_curHP = m_maxHP;
	}
	else if (m_curHP + changeAmount > m_curHP) // underflow
	{
		m_curHP = 0;
	}
	else
	{
		m_curHP += changeAmount;
		if (m_curHP > m_maxHP) m_curHP = m_maxHP;
	}

	// ����ü�� 0
	if (m_curHP == 0)
	{
		m_fsm->ChangeState(STATE_TYPE::DEAD);
	}
}