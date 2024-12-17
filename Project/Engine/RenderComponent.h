#pragma once
#include "Component.h"
#include "IRenderable.h"
#include "Material.h"

// 상수버퍼 연동 구조체
struct CB_Instance
{
	float direction;
	byte padding[12];
};

// 렌더링 담당 컴포넌트
// 게임오브젝트는 한 종류의 렌더컴포넌트만 가질 수 있음
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