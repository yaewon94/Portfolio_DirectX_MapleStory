#pragma once
#include "Component.h"
#include "State.h"

// 게임오브젝트의 상태 머신 컴포넌트
class FSM final : public Component
{
	NO_COPY_MOVE(FSM)
	COMPONENT_TYPE_DCL(COMPONENT_TYPE::FSM)

private:
	unordered_map<STATE_TYPE, State*> m_stateMap;
	State* m_curState;
	void* m_stateData;
	STATE_TYPE m_curStateType;

public:
	FSM(GameObject* const owner);
	FSM(const FSM& origin, GameObject* const newOwner);
	~FSM();

private: // GameObject : Component* 를 통해 호출
	virtual void Init() final;
	virtual void FinalTick() final;

public:
	STATE_TYPE GetCurrentState() const { return m_curStateType; }

	void ChangeState(STATE_TYPE type, void* data = nullptr);

	template<typename T> requires std::derived_from<T, State>
	void AddState(STATE_TYPE type)
	{
		if (m_stateMap.find(type) != m_stateMap.end())
		{
			MessageBox(nullptr, L"같은 state가 이미 존재합니다", L"상태 추가 실패", MB_OK);
			return;
		}

		m_stateMap.insert(make_pair(type, new T(this)));
		if (m_stateMap.size() == 1) m_curState = m_stateMap.find(type)->second;
	}

	void* GetStateData() const { return m_stateData; }

private: // GameObject::복사생성자 에서 호출
	virtual FSM* Clone(GameObject* const newOwner) final { return new FSM(*this, newOwner); }
};