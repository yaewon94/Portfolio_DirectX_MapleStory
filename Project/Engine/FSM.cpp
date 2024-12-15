#include "pch.h"
#include "FSM.h"

FSM::FSM(GameObject* const owner) 
	: Component(owner)
	, m_curState(nullptr), m_curStateType(STATE_TYPE::DEFAULT)
{
}

FSM::FSM(const FSM& origin, GameObject* const newOwner) 
	: Component(origin, newOwner)
	, m_curState(nullptr), m_curStateType(STATE_TYPE::DEFAULT)
{
	for (const auto& pair : origin.m_stateMap)
	{
		pair.second->Clone(this);
	}
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
	if (m_curState == nullptr)
	{
#ifdef _DEBUG
		assert(nullptr);
#else
		return;
#endif // _DEBUG
	}
	m_curState->OnStateTick();
}

void FSM::ChangeState(STATE_TYPE type)
{
	unordered_map<STATE_TYPE, State*>::const_iterator iter = m_stateMap.find(type);
	if (iter == m_stateMap.end())
	{
#ifdef _DEBUG
		assert(nullptr);
#else
		return;
#endif // _DEBUG
	}
	if (m_curState) m_curState->OnStateExit();
	m_curStateType = type;
	m_curState = iter->second;
	m_curState->OnStateEnter();
}