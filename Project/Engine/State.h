#pragma once
#include "Entity.h"

enum class STATE_TYPE : byte
{
	DEFAULT, MOVE, JUMP, ATTACK, HIT, DEAD
};

// 게임오브젝트의 상태
class State : public Entity
{
	NO_COPY_MOVE(State);
	friend class FSM;

private:
	class FSM* m_fsm;

protected:
	State(FSM* const fsm);
	State(const State& origin, FSM* const newOwner);
	~State();
	virtual State* const Clone(FSM* const newOwner) = 0;

protected:
	virtual void Init() {}
	virtual void OnStateEnter() {}
	virtual void OnStateTick() {}
	virtual void OnStateExit() {}

protected:
	FSM* const GetFSM() const { return m_fsm; }

private:
	virtual Entity* Clone() final { return nullptr; } // delete

protected:
	void* operator new(size_t size) { return ::operator new(size); }
	void* operator new[](size_t) = delete;
	void operator delete(void* ptr) { ::operator delete(ptr); }
	void operator delete[](void*) = delete;
};