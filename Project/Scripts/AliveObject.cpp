#include "pch.h"
#include "AliveObject.h"
#include "Engine/GameObject.h"
#include "Engine/FlipbookPlayer.h"
#include "Engine/FSM.h"

AliveObject::AliveObject(GameObject* const owner) 
	: Script(owner)
	, m_flipbookPlayer(nullptr), m_fsm(nullptr)
{
}

AliveObject::AliveObject(const AliveObject& origin, GameObject* const newOwner) 
	: Script(origin, newOwner)
	, IMovable(origin.m_moveSpeed)
{
	m_flipbookPlayer = GetOwner()->GetComponent<FlipbookPlayer>();
	m_fsm = GetOwner()->GetComponent<FSM>();
}

AliveObject::~AliveObject()
{
}