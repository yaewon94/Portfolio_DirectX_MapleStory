#include "pch.h"
#include "AliveObject.h"
#include "Engine/GameObject.h"
#include "Engine/FlipbookPlayer.h"

AliveObject::AliveObject(GameObject* const owner) 
	: Script(owner)
	, m_flipbookPlayer(nullptr)
{
}

AliveObject::AliveObject(const AliveObject& origin, GameObject* const newOwner) 
	: Script(origin, newOwner)
{
	m_flipbookPlayer = GetOwner()->GetComponent<FlipbookPlayer>();
}

AliveObject::~AliveObject()
{
}