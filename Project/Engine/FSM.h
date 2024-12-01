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
	void ChangeState(const string& name);

	template<typename T> requires std::derived_from<T, State>
	void AddState(const string& name)
	{
		if (m_stateMap.find(name) != m_stateMap.end())
		{
			MessageBox(nullptr, L"같은 이름의 state가 이미 존재합니다", L"상태 추가 실패", MB_OK);
			return;
		}

		m_stateMap.insert(make_pair(name, new T(this)));
	}

private: // GameObject::복사생성자 에서 호출
	virtual FSM* Clone(GameObject* const newOwner) final { return new FSM(*this, newOwner); }
};