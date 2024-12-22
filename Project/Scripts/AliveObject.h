#pragma once
#include "Engine/Script.h"
#include "IMovable.h"

typedef UINT HP;
typedef HP Power;

// 플레이어, 몬스터 등 상태를 가지고 있고, 이동가능, 스킬사용가능 등의 특징을 가진 오브젝트
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

protected: // GameObject : Component* 를 통해 호출
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
	// 현재 체력에 반영
	// TODO : HP 타입을 signed 로 바꿀 경우 overflow, underflow 조건체크코드 바꿔야 함
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

	// 현재체력 0
	if (m_curHP == 0)
	{
		m_fsm->ChangeState(STATE_TYPE::DEAD);
	}
}