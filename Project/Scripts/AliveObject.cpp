#include "pch.h"
#include "AliveObject.h"
#include "Engine/GameObject.h"
#include "Engine/FlipbookPlayer.h"

AliveObject::AliveObject(GameObject* const owner) 
	: Script(owner)
	, m_maxHP(100), m_curHP(m_maxHP), m_power(100)
	, m_flipbookPlayer(nullptr), m_fsm(nullptr)
{
}

AliveObject::AliveObject(const AliveObject& origin, GameObject* const newOwner) 
	: Script(origin, newOwner)
	, IMovable(origin.m_moveSpeed)
	, m_maxHP(origin.m_maxHP), m_curHP(m_maxHP), m_power(origin.m_power)
{
	m_flipbookPlayer = GetOwner()->GetComponent<FlipbookPlayer>();
	m_fsm = GetOwner()->GetComponent<FSM>();
}

AliveObject::~AliveObject()
{
}

void AliveObject::Init()
{
	GetOwner()->GetRenderComponent()->GetConstBuffer().direction = (float)m_moveDir;
}