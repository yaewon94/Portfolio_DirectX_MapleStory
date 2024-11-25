#include "pch.h"
#include "Component.h"

Component::Component(GameObject* const owner) 
	: m_owner(owner)
{
}

Component::~Component()
{
	m_owner = nullptr;
}