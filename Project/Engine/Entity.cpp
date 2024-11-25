#include "pch.h"
#include "Entity.h"

UINT Entity::nextID = 0;

Entity::Entity() 
	: m_ID(nextID++)
{
}

Entity::Entity(const Entity& origin) 
	: m_ID(nextID++)
{
}

Entity::~Entity()
{
}
