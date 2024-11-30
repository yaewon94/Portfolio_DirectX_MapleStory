#pragma once
#include "Component.h"
#include "IDebugRenderable.h"

// 게임오브젝트끼리 충돌을 판별하기 위한 컴포넌트
#ifdef _DEBUG
class Collider final : public Component, public IDebugRenderable
#elif
class Collider final : public Component
#endif // _DEBUG
{
	NO_COPY_MOVE(Collider)
	COMPONENT_TYPE_DCL(COMPONENT_TYPE::COLLIDER)

private:
	Vec2 m_offset;
	Vec2 m_scale; // 게임오브젝트 크기에 대한 비율
	Matrix m_matWorld;

public:
	Collider(GameObject* const owner);
	Collider(const Collider& origin, GameObject* const newOwner);
	~Collider();

private: // GameObject : Component* 를 통해 호출
	virtual void Init() final;
	virtual void FinalTick() final;

public:
	const Matrix& GetWorldMatrix() const { return m_matWorld; }

	Vec2 GetOffset() const { return m_offset; }
	void SetOffset(Vec2 offset) { m_offset = offset; }

	Vec2 GetScale() const { return m_scale; }
	void SetScale(Vec2 scale) { m_scale = scale; }

private: // GameObject::복사생성자 에서 호출
	virtual Collider* Clone(GameObject* const newOwner) final { return new Collider(*this, newOwner); }

#ifdef _DEBUG
private:
	SharedPtr<class Material> m_material;
	SharedPtr<class Mesh> m_mesh;
	virtual void Render() final;
#endif // _DEBUG
};