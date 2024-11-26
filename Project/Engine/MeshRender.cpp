#include "pch.h"
#include "MeshRender.h"
#include "Mesh.h"
#include "Material.h"
#include "GameObject.h"
#include "Transform.h"

MeshRender::MeshRender(GameObject* const owner) 
	: RenderComponent(owner)
{
}

MeshRender::MeshRender(const MeshRender& origin, GameObject* const newOwner) 
	: RenderComponent(origin, newOwner)
	, m_mesh(origin.m_mesh)
{
}

MeshRender::~MeshRender()
{
}

void MeshRender::Render()
{
	if (GetMaterial() == nullptr || m_mesh == nullptr) return;

	GetOwner()->GetTransform()->Binding();
	GetMaterial()->Binding();
	m_mesh->Render();
}