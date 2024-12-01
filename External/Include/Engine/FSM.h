#pragma once
#include "Component.h"

class State;

// ���ӿ�����Ʈ�� ���� �ӽ� ������Ʈ
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

private: // GameObject : Component* �� ���� ȣ��
	virtual void FinalTick() final;

public:
	void AddState(const string& name, State* const state);
	void ChangeState(const string& name);

private: // GameObject::��������� ���� ȣ��
	virtual FSM* Clone(GameObject* const newOwner) final { return new FSM(*this, newOwner); }
};