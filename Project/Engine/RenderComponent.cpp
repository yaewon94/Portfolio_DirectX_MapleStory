#include "pch.h"
#include "RenderComponent.h"

RenderComponent::RenderComponent(GameObject* const owner) 
	: Component(owner)
	, m_cb{}
{
}

RenderComponent::RenderComponent(const RenderComponent& origin, GameObject* const newOwner) 
	: Component(origin, newOwner)
	, m_material(origin.m_material)
	, m_cb(origin.m_cb)
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::Binding()
{
	ConstBuffer* cb = Device::GetInstance()->GetConstBuffer(CONST_BUFFER_TYPE::INSTANCE);
	cb->SetData(&m_cb);
	cb->Binding_GS();
}