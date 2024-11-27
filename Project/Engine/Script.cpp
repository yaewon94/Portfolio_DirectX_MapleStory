#include "pch.h"
#include "Script.h"

Script::Script(GameObject* const owner) 
	: Component(owner)
{
}

Script::Script(const Script& origin, GameObject* const newOwner) 
	: Component(origin ,newOwner)
{
}

Script::~Script()
{
}