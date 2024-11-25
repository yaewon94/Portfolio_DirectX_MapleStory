#include "pch.h"
#include "Component.h"

Component::Component(GameObject* const owner) 
	: m_owner(owner)
{
}

Component::Component(const Component& origin, GameObject* const newOwner) 
	: m_owner(newOwner)
{
}

Component::~Component()
{
	m_owner = nullptr;
}