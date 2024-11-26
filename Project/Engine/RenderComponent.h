#pragma once
#include "Component.h"
#include "IRenderable.h"

class Material;

// ������ ��� ������Ʈ
// ���ӿ�����Ʈ�� �� ������ ����������Ʈ�� ���� �� ����
class RenderComponent : public Component, public IRenderable
{
	NO_COPY_MOVE(RenderComponent);

private:
	SharedPtr<Material> m_material;

protected:
	RenderComponent(GameObject* const owner);
	RenderComponent(const RenderComponent& origin, GameObject* const newOwner);
	~RenderComponent();

public:
	SharedPtr<Material> GetMaterial() const { return m_material; }
	void SetMaterial(SharedPtr<Material> material) { m_material = material; }

protected:
	virtual void FinalTick() override {}
};