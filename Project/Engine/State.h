#pragma once
#include "Entity.h"

// 게임오브젝트의 상태
class State : public Entity
{
	NO_COPY_MOVE(State);
	friend class FSM;

private:
	class FSM* m_fsm;

protected:
	State();
	~State();

protected:
	virtual void OnStateEnter() = 0;
	virtual void OnStateTick() = 0;
	virtual void OnStateExit() = 0;

protected:
	FSM* const GetOwner() const { return m_fsm; }

private:
	virtual Entity* Clone() final { return nullptr; } // delete
};