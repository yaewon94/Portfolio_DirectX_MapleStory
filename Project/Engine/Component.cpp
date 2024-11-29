#include "pch.h"
#include "Component.h"

Component::Component(GameObject* const owner) 
	: m_owner(owner)
{
	//this->Init(); // virtual �ȸ���
}

Component::Component(const Component& origin, GameObject* const newOwner) 
	: m_owner(newOwner)
{
	//this->Init(); // virtual �ȸ���
}

Component::~Component()
{
	m_owner = nullptr;
}