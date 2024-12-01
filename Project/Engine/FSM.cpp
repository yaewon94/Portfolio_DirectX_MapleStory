#include "pch.h"
#include "FSM.h"
#include "State.h"

FSM::FSM(GameObject* const owner) 
	: Component(owner)
	, m_curState(nullptr)
{
}

FSM::FSM(const FSM& origin, GameObject* const newOwner) 
	: Component(origin, newOwner)
	, m_curState(nullptr)
{
}

FSM::~FSM()
{
	for (auto& pair : m_stateMap)
	{
		if (pair.second != nullptr)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}
}

void FSM::FinalTick()
{
	if (m_curState) m_curState->OnStateTick();
}

void FSM::AddState(const string& name, State* const state)
{
	if (m_stateMap.find(name) != m_stateMap.end())
	{
		MessageBox(nullptr, L"같은 이름의 state가 이미 존재합니다", L"상태 추가 실패", MB_OK);
		return;
	}
	m_stateMap.insert(make_pair(name, state));
	state->m_fsm = this;
}

void FSM::ChangeState(const string& name)
{
	unordered_map<string, State*>::const_iterator iter = m_stateMap.find(name);
	if (iter == m_stateMap.end())
	{
#ifdef _DEBUG
		assert(nullptr);
#else
		return;
#endif // _DEBUG
	}
	if (m_curState) m_curState->OnStateExit();
	m_curState = iter->second;
	m_curState->OnStateEnter();
}