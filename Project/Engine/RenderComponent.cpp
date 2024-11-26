#include "pch.h"
#include "RenderComponent.h"
#include "Material.h"

RenderComponent::RenderComponent(GameObject* const owner) 
	: Component(owner)
{
}

RenderComponent::RenderComponent(const RenderComponent& origin, GameObject* const newOwner) 
	: Component(origin, newOwner)
	, m_material(origin.m_material)
{
}

RenderComponent::~RenderComponent()
{
}