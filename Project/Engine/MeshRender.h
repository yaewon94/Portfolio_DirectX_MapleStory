#pragma once
#include "RenderComponent.h"
#include "Mesh.h"

// 다각형 렌더링 컴포넌트
class MeshRender : public RenderComponent
{
	NO_COPY_MOVE(MeshRender)
	COMPONENT_TYPE_DCL(COMPONENT_TYPE::MESH_RENDER)

private:
	SharedPtr<Mesh> m_mesh;

public:
	MeshRender(GameObject* const owner);
	MeshRender(const MeshRender& origin, GameObject* const newOwner);
	~MeshRender();

protected: // GameObject : RenderComponent* 를 통해 호출
	virtual void Render() override;

public:
	SharedPtr<Mesh> GetMesh() const { return m_mesh; }
	void SetMesh(SharedPtr<Mesh> mesh) { m_mesh = mesh; }

private:
	virtual MeshRender* Clone(GameObject* const newOwner) override { return new MeshRender(*this, newOwner); }
};