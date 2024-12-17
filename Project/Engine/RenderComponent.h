#pragma once
#include "Component.h"
#include "IRenderable.h"
#include "Material.h"

// ������� ���� ����ü
struct CB_Instance
{
	float direction;
	byte padding[12];
};

// ������ ��� ������Ʈ
// ���ӿ�����Ʈ�� �� ������ ����������Ʈ�� ���� �� ����
class RenderComponent : public Component, public IRenderable
{
	NO_COPY_MOVE(RenderComponent);

private:
	SharedPtr<Material> m_material;
	CB_Instance m_cb;

protected:
	RenderComponent(GameObject* const owner);
	RenderComponent(const RenderComponent& origin, GameObject* const newOwner);
	~RenderComponent();

public:
	SharedPtr<Material> GetMaterial() const { return m_material; }
	void SetMaterial(SharedPtr<Material> material) { m_material = material; }

	CB_Instance& GetConstBuffer() { return m_cb; }

protected:
	virtual void FinalTick() override {}
	void Binding();
};