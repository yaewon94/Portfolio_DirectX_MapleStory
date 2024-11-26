#pragma once
#include "RenderComponent.h"

class Mesh;

// ´Ù°¢Çü ·»´õ¸µ ÄÄÆ÷³ÍÆ®
class MeshRender final : public RenderComponent
{
	NO_COPY_MOVE(MeshRender)
	COMPONENT_TYPE_DCL(COMPONENT_TYPE::MESH_RENDER)

private:
	SharedPtr<Mesh> m_mesh;

public:
	MeshRender(GameObject* const owner);
	MeshRender(const MeshRender& origin, GameObject* const newOwner);
	~MeshRender();
	virtual MeshRender* Clone(GameObject* const newOwner) final { return new MeshRender(*this, newOwner); }


public:
	virtual void Render() final;

public:
	SharedPtr<Mesh> GetMesh() const { return m_mesh; }
	void SetMesh(SharedPtr<Mesh> mesh) { m_mesh = mesh; }
};