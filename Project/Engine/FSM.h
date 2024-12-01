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
	void ChangeState(const string& name);

	template<typename T> requires std::derived_from<T, State>
	void AddState(const string& name)
	{
		if (m_stateMap.find(name) != m_stateMap.end())
		{
			MessageBox(nullptr, L"���� �̸��� state�� �̹� �����մϴ�", L"���� �߰� ����", MB_OK);
			return;
		}

		m_stateMap.insert(make_pair(name, new T(this)));
	}

private: // GameObject::��������� ���� ȣ��
	virtual FSM* Clone(GameObject* const newOwner) final { return new FSM(*this, newOwner); }
};