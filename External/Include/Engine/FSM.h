#pragma once
#include "Component.h"

class State;

// 게임오브젝트의 상태 머신 컴포넌트
class FSM final : public Component
{
	NO_COPY_MOVE(FSM)
	COMPONENT_TYPE_DCL(COMPONENT_TYPE::FSM)

private:
	unordered_map<string, State*> m_stateMap;
	State* m_curState;

public:
	FSM(GameObject* const owner);
	FSM(const FSM& origin, GameObject* const newOwner);
	~FSM();

private: // GameObject : Component* 를 통해 호출
	virtual void FinalTick() final;

public:
	void AddState(const string& name, State* const state);
	void ChangeState(const string& name);

private: // GameObject::복사생성자 에서 호출
	virtual FSM* Clone(GameObject* const newOwner) final { return new FSM(*this, newOwner); }
};