#include "pch.h"
#include "Ground.h"
#include "Engine/GameObject.h"
#include "Engine/Collider.h"

Ground::Ground(GameObject* const owner) 
	: Script(owner)
{
	Init();
}

Ground::Ground(const Ground& origin, GameObject* const newOwner) 
	: Script(origin, newOwner)
{
	Init();
}

Ground::~Ground()
{
}

void Ground::Init()
{
	GetOwner()->SetTag(OBJECT_TAG::TAG_GROUND);
	GetOwner()->AddComponent<Collider>();
}