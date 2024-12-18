#include "pch.h"
#include "Ground.h"
#include "Engine/GameObject.h"
#include "Engine/Collider.h"

Ground::Ground(GameObject* const owner) 
	: Script(owner)
{
	GetOwner()->AddComponent<Collider>();
}

Ground::Ground(const Ground& origin, GameObject* const newOwner) 
	: Script(origin, newOwner)
{
}

Ground::~Ground()
{
}

void Ground::Init()
{
	GetOwner()->SetTag(OBJECT_TAG::TAG_GROUND);
}