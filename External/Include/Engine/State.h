#pragma once
#include "Entity.h"

class State : public Entity
{
	NO_COPY_MOVE(State);

protected:
	State();
	~State();

protected:
	virtual void OnStateEnter() = 0;
	virtual void OnStateTick() = 0;
	virtual void OnStateExit() = 0;

private:
	virtual Entity* Clone() final { return nullptr; } // delete
};